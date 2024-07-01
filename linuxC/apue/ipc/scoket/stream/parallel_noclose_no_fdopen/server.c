#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>          
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "proto.h"
#define IPSTRSIZE 40
#define BUFSIZE 1024
// 并发版
static void server_job(int sd){
    // 给客户端返回数据
    char buf[BUFSIZE];
    int len = sprintf(buf, FMT_STAMP, (long long)time(NULL));
    // 这里没有字节序的问题，是因为把这个时间给转成了字符串，是以字符为单位进行存储的，所以没有字节序的问题
    if (send(sd, buf, len, 0)<0) {
        perror("send()");
        exit(1);
    }
}
int main(int argc, char *argv[]){
    int sd;
    struct sockaddr_in ladqdr,raddr;
    socklen_t raddr_len;
    char ipstr[IPSTRSIZE];
    //1、建立socket
    sd= socket(AF_INET,SOCK_STREAM,0);//0 表示使用AF_INET中的默认协议IPPROTO_TCP，类似的还有IPPROTO_SCTP 
    if (sd<0) {
        perror("socket()");
        exit(1);
    }
    int val =1;
    if(setsockopt(sd, SOL_SOCKET, SO_REUSEADDR,&val,sizeof(val))<0){
        perror("setsockopt()");
        exit(1);
    }
     // 设置协议族
    ladqdr.sin_family =AF_INET;
    // 把端口号从主机序转成网络序
    // 这里使用htonl 再去查看绑定的端口
    ladqdr.sin_port = htons(atoi(SERVERPORT));
    // 把一个字符串类型的ipv4地址或ipv6地址转成二进制。
    // 也可以用serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);来代替
    // 使用0.0.0.0 全零的ip地址，是为了让socket在绑定时使用任意可用的ip地址
    if(inet_pton(AF_INET,"0.0.0.0",&ladqdr.sin_addr.s_addr)<0){
        fprintf(stderr, "inet_pton\n");
        exit(1);
    }
    //2、 分配IP地址和端口号
    if(bind(sd, (void *)&ladqdr,sizeof(ladqdr))<0){
        perror("bind()");
        exit(1);
    }
    // 3、转为可监听状态
   if (listen(sd, 5)<0) {
        perror("listen()");
        exit(1);
   }
    raddr_len = sizeof(raddr);
    while (1) {
        int newsd = accept(sd, (void * )&raddr, &raddr_len);
        if(newsd<0){
            perror("accept()");
            exit(1);
        }
        pid_t pid = fork();
        if (pid<0) {
            perror("fork()");
            exit(1);
        }
        if (pid==0) {
            //close(sd);
            inet_ntop(AF_INET, &raddr.sin_addr, ipstr, IPSTRSIZE);
            printf("Client:%s:%d\n",ipstr, ntohs(raddr.sin_port));
            server_job(newsd);
            // 关闭新的socket
            close(newsd);
            // 退出这个程序。
            exit(0);
        }
       // close(newsd);

        
    }
    close(sd);
    
}