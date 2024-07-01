#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>          
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>
#define IPSTRSIZE 40
// 报式传输
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
    raddr.sin_port = htons(80);
    FILE*  fp=NULL;
    char rbuf[BUFSIZ];
    inet_pton(AF_INET, argv[1], &raddr.sin_addr);

    // bind();可以省略
    if(connect(sd, (void*)&raddr, sizeof(raddr))<0){
        perror("connect()");
        exit(1);
    }
     // 将socket 转成文件流，这样就使用标准io进行操作了，这样的话，打印内容，似乎就不用考虑字节序的问题了貌似。
    fp =  fdopen(sd,"r+");
    if (fp ==NULL) {
        perror("fdopen()");
        // 这里应该加上一些钩子函数，释放资源
        exit(1);
    }
    // fprintf+ fflush就相当于是执行了send。
    // fprintf(fp, "GET /cover.png\r\n\r\n");
    // fflush(fp);
    // 使用send 发送消息
    char * msg = "GET /cover.png\r\n\r\n";
    if(send(sd, msg, strlen(msg), 0)<0){
        perror("send()");
        exit(1);
    }
    while (1) {
       int len= fread(rbuf,1,BUFSIZ,fp);
       if (len <=0) {
            break;
       }
       fwrite(rbuf, 1, len, stdout);
    }
    fclose(fp);
    //rcev()
    //close
}