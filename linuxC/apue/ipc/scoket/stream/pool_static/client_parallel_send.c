#include <stdlib.h>
#include <stdio.h>
#include "proto.h"
#include <sys/types.h>          
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>
#define IPSTRSIZE 40
// fork 多个子进程同时给server发消息， 这个主要是为了测试一下listen函数中的backlog参数
#define PROCNUM 30

static void sendRequest(char *argv[]){
    int sd=socket(AF_INET, SOCK_STREAM, 0);
    if (sd <0) {
        perror("socket()");
        exit(1);
    }
    struct sockaddr_in raddr;
    raddr.sin_family = AF_INET;
    raddr.sin_port = htons(atoi(SERVERPORT));
    FILE*  fp=NULL;
    inet_pton(AF_INET, argv[1], &raddr.sin_addr);
    printf("send reqeust,pid:%d\n", getpid());

    // bind();可以省略
    if(connect(sd, (void*)&raddr, sizeof(raddr))<0){
        perror("connect()");
        exit(1);
    }
    printf("connect\n");
     // 将socket 转成文件流，这样就使用标准io进行操作了，这样的话，打印内容，似乎就不用考虑字节序的问题了貌似。
    fp =  fdopen(sd,"r+");
    if (fp ==NULL) {
        perror("fdopen()");
        // 这里应该加上一些钩子函数，释放资源
        exit(1);
    }
    long long stamp ;
    if (fscanf(fp, FMT_STAMP, &stamp)<1) {
        fprintf(stderr, "Bad format!\n");
    }else {
        fprintf(stdout, "stamp=%lld,pid=%d\n",stamp, getpid());
    }
    fclose(fp);
}
int main(int argc, char *argv[]){
    if (argc<2) {
        fprintf(stderr, "Usage...\n");
        exit(1);
    }
    for (int i=0; i<PROCNUM; i++) {
        pid_t pid = fork();
        if (pid<0) {
            perror("fork()");
            exit(1);
        }
        if (pid ==0) {
            sendRequest(argv);
            exit(0);
        }
    }
   for (int i=0; i<PROCNUM; i++) {
        wait(NULL);
   }
}