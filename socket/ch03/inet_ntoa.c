#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
int main(int argc,char* argv[]){
    struct sockaddr_in addr1,addr2;
    char * str_ptr;
    char str_arr[20];
    addr1.sin_addr.s_addr = htonl(0x1020304);
    addr2.sin_addr.s_addr=htonl(0x1010101);
    str_ptr=inet_ntoa(addr1.sin_addr);
    strcpy(str_arr,str_ptr);
    printf("Dotted-Decimal notation1:%s \n", str_ptr);
    /*
    * 这里不用在设置返回值str_ptr，正常的应该是str_ptr=inet_ntoa(addr2.sin_addr);
    * 但是由于inet_ntoa 返回的是一个指针，指向的是一个内部的数组，所以在第一次调用的时候，str_ptr 
    * 在第一次调用的时候就指向了inet_ntoa 内部的数组。
    */ 
    inet_ntoa(addr2.sin_addr);
    printf("Dotted-Decimal notation2:%s \n", str_ptr);
    printf("Dotted-Decimal notation3:%s \n", str_arr);
    return 0;
}