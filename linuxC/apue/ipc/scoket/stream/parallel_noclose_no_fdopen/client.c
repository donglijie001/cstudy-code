#include <stdlib.h>
#include <stdio.h>
#include "proto.h"
#include <string.h>
#include <sys/types.h>          
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>
#define IPSTRSIZE 40
// 流式传输，这里不使用fdopen，并且 server 也没有使用close函数。
int main(int argc, char *argv[]){
    if (argc<2) {
        fprintf(stderr, "Usage...\n");
        exit(1);
    }
    int sd=socket(AF_INET, SOCK_STREAM, 0);
    if (sd <0) {
        perror("socket()");
        exit(1);
    }
    struct sockaddr_in raddr;
    raddr.sin_family = AF_INET;
    raddr.sin_port = htons(atoi(SERVERPORT));
    FILE*  fp=NULL;
    char rbuf[BUFSIZ];
    inet_pton(AF_INET, argv[1], &raddr.sin_addr);

    // bind();可以省略
    if(connect(sd, (void*)&raddr, sizeof(raddr))<0){
        perror("connect()");
        exit(1);
    }
    if(recv(sd, rbuf, sizeof(rbuf), 0)<0){
        // 接收消息出错
        perror("recv()");
        exit(1);
    }
    printf("%ld\n", (long)strlen(rbuf));
    printf("%s\n", rbuf);
    //  // 将socket 转成文件流，这样就使用标准io进行操作了，这样的话，打印内容，似乎就不用考虑字节序的问题了貌似。
    // fp =  fdopen(sd,"r+");
    // if (fp ==NULL) {
    //     perror("fdopen()");
    //     // 这里应该加上一些钩子函数，释放资源
    //     exit(1);
    // }
    // long long stamp ;
    // if (fscanf(fp, FMT_STAMP, &stamp)<1) {
    //     fprintf(stderr, "Bad format!\n");
    // }else {
    //     fprintf(stdout, "stamp=%lld \n",stamp);
    // }
    // fclose(fp);
    //rcev()
    //close
}