#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "mytbf.h"

#define CPS 10 // 每秒传输的字符
#define  BUF_SIZ__ 1024
#define BURST 100
static volatile int  token =0;
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
    mytbf_t * tbf = mytbf_init(CPS, BURST);
    if (tbf==NULL) {
        // 
        fprintf(stderr, "mytbf_init() error");
        exit(1);
    }
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
        // 尝试获取BUF_SIZ__个token，但是最终能获取多少，需要通过返回值来判断。
       int size= mytbf_fetchtoken(tbf,  BUF_SIZ__);
       if (size < 0) {
            // 出错直接返回
            fprintf(stderr, "mytbf_fetchtoken():%s\n", strerror(-size));
            exit(1);
       }
       while ((len= read(sfd, buf, size))<0) {
            if (errno == EINTR) {
                continue;
            }
            perror("read");
            break;
       };
       if (len==0) {
            break;
       }
       //需要判断一下token到底用了多少，如果没有用完，需要把token给返回
       int token_resrvered_count=size-len;
       if (token_resrvered_count>0) {
        mytbf_returntoken(tbf, token_resrvered_count);
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
    mytbf_destory(tbf);
    exit(0);
}