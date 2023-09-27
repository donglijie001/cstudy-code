#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#define  BUF_SIZ__ 1024
int main(int argc,char ** argv){
    if (argc<3) {
        fprintf(stderr, "Usage%s <src_file> <dest_file>\n",argv[0]);
        exit(1);
    }
    int sfd, dfd;
    sfd =open(argv[1],O_RDONLY);
    char buf[BUF_SIZ__];
    int len;
    int ret;
    int pos;
    if (sfd<0) {
        perror("open()");
        exit(1);
    }
    // 文件存在就以只写打开，否则就创建，如果文件以只写打开，就把文件截断（通过O_TRUNC 来指定)。
    dfd=open(argv[2],O_WRONLY|O_CREAT,O_TRUNC, 0600);
    if (dfd<0) {
        // 源文件已经打开了，这个时候需要关闭
        close(sfd);
        perror("open()");
        exit(1);

    }


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
                perror("write()");
                // 把文件给关闭。
                close(dfd);
                close(sfd);
                exit(1);
            }
            pos += ret;
            len -= ret;
       }
      
    }
    close(dfd);
    close(sfd);

    exit(0);
}