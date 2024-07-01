#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#define TTY1 "/dev/tty11"
#define TTY2 "/dev/tty12"
#define BUFSIZE 1024
/**
 * 使用select函数，改成非盲等
运行程序输出内容：一开始 fd1和fd2都是读set里
 issue monitor task
rset add fsm12.sfd
rset add fsm21.sfd
当我在tty11上输入内容后，select 监听到读set里的文件描述符有内容可读，就会往下走
发现fd1在读set里，这个时候就会调用fsm_driver(&fsm12)，fsm12 会从读态变成写态，所以输出下面两行内容
fd1 in rset
fsm_driver(&fsm12)
紧接着，while循环又进行，这个时候，fd2就会被加到写set里，同时fd2也会被加到读set里，这时候fd1 并没有被加到
任何一个set里
issue monitor task
wset add fsm12.dfd
rset add fsm21.sfd
fd2被加到写set里，select 这个时候，就立刻监听到，fd2是可以被写入内容的，然后就返回，这个时候判断
fd2 在写set里，然后调用fsm_driver(&fsm12) ，就会往fd2里面写入内容，fsm12 就从写态变成读态
fd2 in wset
fsm_driver(&fsm12)
//fsm_driver(&fsm12) 执行完后，while循环，再次判断，这个时候，就把fd1和fd2 又加到读set里了

issue monitor task
rset add fsm12.sfd
rset add fsm21.sfd
 * 
 */
enum{
    STATE_R=1,
    STATE_W,
    STATE_AUTO,
    STATE_Ex,// 异常
    STATE_T,//退出
};
struct fsm_st{
    int state;
    int sfd;
    int dfd;
    int len;
    int pos;// 记录写入的位置，因为可能一次无法完全写入
    char buf[BUFSIZE];
    char * errstring;
};
static void fsm_driver(struct fsm_st * fsm){
    int ret;
    switch (fsm->state) {
        case STATE_R:
            fsm->len =read(fsm->sfd, fsm->buf, BUFSIZE);
            if (fsm->len==0) {
                fsm->state = STATE_T;
            }else if (fsm->len <0) {
                if (errno==EAGAIN) { //如果是假错，继续切换到读态
                 fsm->state = STATE_R;
                }else {
                fsm->errstring="read()";
                 fsm->state = STATE_Ex;
                }
            }else {
                fsm->pos=0;
                fsm->state = STATE_W;
            }
                break;
        case STATE_W:
           ret= write(fsm->dfd, fsm->buf+fsm->pos, fsm->len);
           if (ret<0) {
                if (errno==EAGAIN) { 
                 fsm->state = STATE_W;
                }else {
                fsm->errstring="write()";

                 fsm->state = STATE_Ex;
                }
           }else {
                fsm->pos+=ret;
                fsm->len -= ret;
                if (fsm->len==0) {
                    // 把数据全部读完了。
                    fsm->state=STATE_R;
                }else{
                    // 没有写完，继续写。
                    fsm->state = STATE_W;
                }
           }
                break;
        case STATE_Ex:
                perror(fsm->errstring);
                fsm->state=STATE_T;
                break;
        case STATE_T:
                // do somethging,因为这里是两个中端相互之间写来写去，所以暂时做不了啥
                break;
        default:
            abort();
            break;      
    }
}
static int max(int a, int b){
    if (a>b) {
        return a;
    }
    return b;
}
static void relay(int fd1,int fd2){
    // 由于fd1和fd2不知道是否是是nonblock的，所以这里先获取它的文件描述的状态，
    //然后再给他设置成非阻塞的。
    int fd1_save,fd2_save;
    fd_set rset, wset;// 写fd集合和读fd集合
    struct fsm_st fsm12,fsm21; //fsm_12 读1写2，fsm21读2写1
    fd1_save=fcntl(fd1, F_GETFL);
    fcntl(fd1, F_SETFL, fd1_save|O_NONBLOCK);
    fd2_save=fcntl(fd1, F_GETFL);
    fcntl(fd2, F_SETFL, fd2_save|O_NONBLOCK);

    fsm12.state= STATE_R;
    fsm12.sfd=fd1;
    fsm12.dfd = fd2;
     
    fsm21.state= STATE_R;
    fsm21.sfd=fd2;
    fsm21.dfd = fd1;
    // 盲等的原因，因为使用的while ，不停的推任务
    while (fsm12.state !=STATE_T || fsm21.state !=STATE_T) {
        printf("issue monitor task\n");
        // 1、布置监视任务
        //清空set
        FD_ZERO(&rset);
        FD_ZERO(&wset);
        if (fsm12.state==STATE_R) {
            // fsm12状态是读态说明是可以从sfd读数据， fsm12 结构体的设计就是从sfd读数据写到dfd
            printf("rset add fsm12.sfd\n");
            FD_SET(fsm12.sfd, &rset);
        }
        if (fsm12.state==STATE_W) {
            printf("wset add fsm12.dfd\n");

            FD_SET(fsm12.dfd, &wset);
        }
        if (fsm21.state==STATE_R) {
            printf("rset add fsm21.sfd\n");
            FD_SET(fsm21.sfd, &rset);
        }
        if (fsm21.state==STATE_W) {
            printf("wset add fsm21.dfd\n");

            FD_SET(fsm21.dfd, &wset);
        }

        // 2、监视
        if (fsm12.state<STATE_AUTO || fsm21.state<STATE_AUTO) {
                // 发生假错以后，要重新布置监视任务，所以下面这条语句不能使用while，要使用if
            
            if (select(max(fd1, fd2)+1,&rset, &wset, NULL,NULL) <0) {
                    if (errno == EINTR) {
                        // 发生了假错，重新布置监视任务。
                        continue;
                    }
                    perror("select()");
                    exit(1);
            };

        }
        // 3、查看监视结果
        if (FD_ISSET(fd1, &rset)) {
            printf("fd1 in rset\n");
        }
        if (FD_ISSET(fd2, &wset)) {
            printf("fd2 in wset\n");
        }
        if (FD_ISSET(fd2, &rset)) {
            printf("fd2 in rset\n");
        }
        if (FD_ISSET(fd1, &wset)) {
            printf("fd2 in wset\n");
        }
        // 这里只推动了写态和读态，没有考虑异常态和终止态
        if (FD_ISSET(fd1, &rset)|| FD_ISSET(fd2, &wset) || fsm12.state> STATE_AUTO) {
            printf("fsm_driver(&fsm12)\n");
            fsm_driver(&fsm12);
        }
        if (FD_ISSET(fd2, &rset)|| FD_ISSET(fd1, &wset)|| fsm21.state> STATE_AUTO) {
            printf("fsm_driver(&fsm21)\n");

            fsm_driver(&fsm21);
        }

    }
    

    fcntl(fd1, F_SETFL, fd1_save);
    fcntl(fd2, F_SETFL, fd2_save);

}
int main(){

    int fd1,fd2;
    fd1 = open(TTY1, O_RDWR);
    if(fd1<0){
        perror("open()");
        exit(1);
    }
    write(fd1, "TTY1\n", 5);
    fd2 =open(TTY2, O_RDWR|O_NONBLOCK);
    if (fd2<0) {
        close(fd1);
        perror("open()");
        exit(1);
    }
    write(fd2, "TTY2\n", 5);

    relay(fd1, fd2);
    
    exit(0);
}