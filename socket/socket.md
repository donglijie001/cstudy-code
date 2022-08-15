# socket编程
以下笔记来源于 TCP/IP 网络编程
接受连接请求的套接字创建过程如下：
- 调用socket函数创建套接字
- 调用bind函数分配IP地址和端口号
- 调用list函数转为可接收请求状态
- 调用accept函数处理连接请求
## 文件描述符
- 0: 标准输入
- 1: 标准输出
- 2: 标准错误
上面这三种是程序开始创建后自动被分配的文件描述符
## 2套接字类型与协议设置
### 创建套接字
```
#include<sys/socket.h>
int socket(int domain,int type,int protocol);
# 成功时返回文件描述符，失败时返回-1.
```
- domain: 套接字中使用的协议族信息
- type： 套接字数据传输类型信息
- protocol：计算机间通信中使用的协议信息
#### 协议族分类
- PF_INET   ipv4 互联网协议族
- PF_INET6  ipv6 互联网协议族
- PF_LOCAL  本地通信的unix协议族
- PF_PACKET 底层套接字的协议族
- PF_IPX    IPX Novell协议族
> 套接字中实际采用的最终协议信息是通过socket函数的第三个参数传递的，在制定的协议族范围内通过第一个参数决定第三个参数
#### 套接字类型type
- SOCK_STREAM 面向连接的套接字，tcp连接，可靠传输
- SOCK_DGRAM 面向消息的套接字，udp数据报，不可靠传输
#### 协议的最终选择
socket 套接字的前两个参数基本上已经可以决定数据传输所采用的协议，所以大部分情况下第三个参数设置为0即可，除非遇到**同一协议族中存在多个数据传输方式相同的协议**
## 地址族与数据序列
### 网络地址的初始化和分配
在sockaddr_in 中保存地址信息的成员为32位整数，因此为了分配ip地址，需要将其表示为32位整数型数据，ip地址一般是点分十进制，可以通过下面这个函数将字符串形式的ip转为32位整型数据。该函数在转换类型的同时也进行网络字节序转换。
```
#include<arpa/inet.h>
in_addr_d inet_addr(const char * string);
```
除了这个函数以外，还有一个函数，inet_aton,使用inet_addr 函数需要将转换后的ip地址放到sockaddr_in结构体中声明的in_addr结构体变量。而inet_aton不用，因为该函数有个参数就是in_addr 指针。
```
#include <arpa/inet.h>
int inet_aton(const char* string, struct in_addr * addr);
// 成功时返回1（true）,失败时返回0（false）
```
下面这个函数将网络字节序整数型ip地址转换为字符串形式。
```
#include<arpa/inet.h>
char * inet_ntoa(struct in_addr adr);
```
网络地址初始化
```
struct sockaddr_in addr;
char* serv_ip = "211.117.168.13"; //声明IP 地址字符串
char * serv_port = "9190"; //声明端口号字符串
memset(&addr,0, sizeof(addr));// 结构体交量addr 的所有成员初始化为0,这么做的目的是为了将sin_zero初始化为0
addr.sin_family = AF_INET;//指定地址族
addr.sin_addr.s_addr = inet_addr(serv_ip);//基于字符亭的IP 地址初始化
addr.sin_port = htons(atoi(serv_port));//基于字符串的端口号初始化
```
#### INADDR_ANY
为了避免每次创建服务端socket都输入ip地址，可以使用INADDR_ANY来代替，使用INADDR_ANY 可以自动获取运行服务器端的计算机ip地址，（如果只有一个网卡的话）。
```
addr.sin_addr.s_addr = htonl(INADDR_ANY);
```
#### 向套接字分配网络地址
```
#include <sys/socket.h>
int bind(int sockfd,struct sockaddr* myaddr,socklen_t addrlen);
# 成功时返回0，失败时返回-1
sockfd 要分配地址信息( I P地址和端口号)的套接字文件描述符。
myaddr 存有地址信息的结构体变量地址值。
addrlen 第二个结构体变量的长度。
```