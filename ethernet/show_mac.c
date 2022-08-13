#include <net/if.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

int main(int charc,char *argv[]){
    // create a socket, any type is ok
    /*
    * https://blog.csdn.net/linglongbayinhe/article/details/83214171
    * domain：表示使用的协议簇，AF_UNIX（本机通信），AF_INET（TCP/IP – IPv4），AF_INET6（TCP/IP – IPv6）
    * type:套接字类型：SOCK_STREAM：TCP流，SOCK_DGRAM：UDP数据报，SOCK_RAW（原始套接字）
    最后一个 “protocol”一般设置为“0”，也就是当确定套接字使用的协议簇和类型时，这个参数的值就为0，但是有时候创建原始套接字时，并不知道要使用的协议簇和类型，也就是domain参数未知情况下，这时protocol这个参数就起作用了，它可以确定协议的种类。
    socket是一个函数，那么它也有返回值，当套接字创建成功时，返回套接字，失败返回“-1”，错误代码则写入“errno”中。
    */
    int s = socket(AF_INET, SOCK_STREAM, 0);
}
