#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#define CPS 10 // 每秒传输的字符
#define  BUF_SIZ__ CPS
static volatile int  loop =0;
static volatile int sfd;
void alrm_handler(int s){
    char buf[BUF_SIZ__];
    int len;
    int ret;
    int dfd =1;
    while ((len= read(sfd, buf, BUF_SIZ__))<0) {
            if (errno == EINTR) {
                continue;
            }
            perror("read");
            break;
       };
       if (len==0) {
            loop =1;
       }
       // 在写数据的时候，可能会出现一种情况就是，要写入的数据没有一次性写入完全。
       while (len >0) {
            ret= write(dfd, buf, len);
            if (ret <0) {
                if (errno==EINTR) {
                    // 被打断，继续
                    continue;
                }
                perror("write()");
                // 把文件给关闭，没有必要关闭终端了
                close(sfd);
                exit(1);
            }
            len -= ret;
       }
}
int main(int argc,char ** argv){
    if (argc<2) {
        fprintf(stderr, "Usage%s <src_file>\n",argv[0]);
        exit(1);
    }
    printf("jhjjddddddd\n");
    do{
        sfd =open(argv[1],O_RDONLY);
        if (sfd<0) {
            if (errno !=EINTR) {
                perror("open()");
                exit(1);
            }
        }
    }while(sfd<0);
    
    // dfd 直接改成1，对应标准输出，这样就会把文件给输出到终端上
    signal(SIGALRM, alrm_handler);
    while (!loop) {
        // 一开始有内容的时候，会定时读，当读到最后的时候，读不到内容了，把loop置为1，停止定时
        //printf("jhjj\n");
        alarm(1);
        pause(); 
        //要加上pause函数，不然，就会陷入死循环，一直在设置定时一秒，
        //新设置的会把旧的给冲掉，永远也打印不出文件内容。
    }
    
    
   
   // close(dfd);
    close(sfd);

    exit(0);
}