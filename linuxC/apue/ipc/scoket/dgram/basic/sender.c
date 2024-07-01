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

int main(int argc, char *argv[]){
    if (argc<2) {
        fprintf(stderr, "Usage...\n");
        exit(1);
    }
    struct msg_st sbuf;
    //1、建立socket
    int sd= socket(AF_INET,SOCK_DGRAM,0);//0 表示使用AF_INET中的默认协议IPPROTO_UDP
    if (sd<0) {
        perror("socket()");
        exit(1);
    }
    struct sockaddr_in  raddr;
    // sendto 用于报式传输，send 用于流式传输
    memset(&sbuf, '\0', sizeof(sbuf));
    strcpy(sbuf.name, "Alan");
    sbuf.math = htonl(rand()%100);
    sbuf.chinese = htonl(rand()%100);

    raddr.sin_family =AF_INET;
    raddr.sin_port = htons(atoi(RCVPORT));
    inet_pton(AF_INET,argv[1],&raddr.sin_addr.s_addr);
    
    if(sendto(sd,&sbuf, sizeof(sbuf),0 ,(void*) &raddr, sizeof(raddr))<0){
        perror("sendto()");
        exit(1);
    }
    
}