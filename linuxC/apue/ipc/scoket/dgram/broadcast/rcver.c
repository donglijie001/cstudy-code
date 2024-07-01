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
// 报式传输
int main(){
    // inet_pton 将ip地址转成数字
    struct msg_st rbuf;
    struct sockaddr_in ladqdr, raddr;
    socklen_t raddr_len;
    char ipstr[IPSTRSIZE];
    //1、建立socket
    int sd= socket(AF_INET,SOCK_DGRAM,0);//0 表示使用AF_INET中的默认协议IPPROTO_UDP
    if (sd<0) {
        perror("socket()");
        exit(1);
    }
    

     // 设置协议族
    ladqdr.sin_family =AF_INET;
    // 把端口号从主机序转成网络序
    // 这里使用htonl 再去查看绑定的端口
    ladqdr.sin_port = htons(atoi(RCVPORT));
    // 把一个字符串类型的ipv4地址或ipv6地址转成二进制。
    // 也可以用serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);来代替
    // 使用0.0.0.0 全零的ip地址，是为了让socket在绑定时使用任意可用的ip地址
    inet_pton(AF_INET,"0.0.0.0",&ladqdr.sin_addr.s_addr);
    //2、 分配IP地址和端口号
    if(bind(sd, (void *)&ladqdr,sizeof(ladqdr))<0){
        perror("bind()");
        exit(1);
    }
    printf("bind success\n");
    // 3、接收消息
    /*recvfrom 适用于报式套接字，UDP的场景，没有事先建立连接
        recv 适用流式套接字，有事先建立连接
    */
    //下面这句话不能省略,否则第一次接收请求，打印的地址是有问题的。
    raddr_len = sizeof(raddr);
    while (1) {
        recvfrom(sd,&rbuf, sizeof(rbuf), 0, (void *)&raddr, &raddr_len);
        // 将ip地址的大整数，转成点分十进制
        inet_ntop(AF_INET, &raddr.sin_addr, ipstr, IPSTRSIZE);
        printf("----MESSAGE FROM %s:%d\n", ipstr, ntohs(raddr.sin_port));
        printf("NAME = %s\n",rbuf.name);
        printf("MATH=%d\n", ntohl(rbuf.math));
        printf("CHINESE=%d\n", ntohl(rbuf.chinese));

    }
    
    close(sd);
    exit(0);
}