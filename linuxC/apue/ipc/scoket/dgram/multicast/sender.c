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
#include <net/if.h>
// 发送组播消息, man 7 socket 
int main(int argc, char *argv[]){
    struct msg_st sbuf;
    //1、建立socket
    int sd= socket(AF_INET,SOCK_DGRAM,0);//0 表示使用AF_INET中的默认协议IPPROTO_UDP
    if (sd<0) {
        perror("socket()");
        exit(1);
    }
    struct ip_mreqn mreq;
    inet_pton(AF_INET, MTGROUP,&mreq.imr_multiaddr);
    inet_pton(AF_INET, "0.0.0.0",&mreq.imr_address);
    // 设置网络索引号
    mreq.imr_ifindex = if_nametoindex("eth0");


    // 创建多播组
    if(setsockopt(sd, IPPROTO_IP, IP_MULTICAST_IF, &mreq, sizeof(mreq))<0){
        perror("setsockopt()");
        exit(1);
    }
    struct sockaddr_in  raddr;
    // sendto 用于报式传输，send 用于流式传输

    strcpy(sbuf.name, "Alan");
    sbuf.math = htonl(rand()%100);
    sbuf.chinese = htonl(rand()%100);

    raddr.sin_family =AF_INET;
    raddr.sin_port = htons(atoi(RCVPORT));
    inet_pton(AF_INET,MTGROUP,&raddr.sin_addr.s_addr);
    
    if(sendto(sd,&sbuf, sizeof(sbuf),0 ,(void*) &raddr, sizeof(raddr))<0){
        perror("sendto()");
        exit(1);
    }
    
}