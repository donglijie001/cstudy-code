#include <stdlib.h>
#include <stdio.h>
#include "proto.h"
#include <sys/types.h>          
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
// 这里从命令行接收名字
int main(int arpc, char *argv[]){
    if (arpc<3) {
        fprintf(stderr, "Usage...\n");
        exit(1);
    }
    //判断名字长度,strlen 计算时不包括尾0，所以要大于
    if (strlen(argv[2])> NAMEMAX) {
        fprintf(stderr, "name is too long\n");
        exit(1);
    }
    struct msg_st *sbufp;
    //1、建立socket
    int sd= socket(AF_INET,SOCK_DGRAM,0);//0 表示使用AF_INET中的默认协议IPPROTO_UDP
    if (sd<0) {
        perror("socket()");
        exit(1);
    }
    struct sockaddr_in  raddr;
    // 这里申请内存的时候，msg_st中的name的长度是1，这个1就相当于是给尾0.
    int size = sizeof(struct msg_st) + strlen(argv[2]);
    sbufp = malloc(size);
    strcpy(sbufp->name, argv[2]);
    sbufp->math = htonl(rand()%100);
    sbufp->chinese = htonl(rand()%100);

    raddr.sin_family =AF_INET;
    raddr.sin_port = htons(atoi(RCVPORT));
    inet_pton(AF_INET,argv[1],&raddr.sin_addr.s_addr);
    // sendto 用于报式传输，send 用于流式传输
    if(sendto(sd,sbufp, size,0 ,(void*) &raddr, sizeof(raddr))<0){
        perror("sendto()");
        exit(1);
    }
    
}