#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#define  BUF_SIZ__ 1024*1024*2
int main(int argc,char ** argv){
    if (argc<2) {
        fprintf(stderr, "Usage%s <src_file>\n",argv[0]);
        exit(1);
    }
    int sfd, dfd;
    
    char buf[BUF_SIZ__];
    int len;
    int ret;
    int pos;
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
    dfd=1;
    while (1) {
       len= read(sfd, buf, BUF_SIZ__);
       if (len<0) {
            perror("read");
            break;
       }
       if (len==0) {
            break;
       }
       pos=0;
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
            pos += ret;
            len -= ret;
       }
      
    }
   // close(dfd);
    close(sfd);

    exit(0);
}