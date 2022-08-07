#include <stdio.h>
#include <argp.h>
struct arguments{
    // 发送数据的网卡地址，使用const声明一个常量，但是这里可以修改iface指向的位置。
    char const *iface;
    // 目的网卡地址
    char const *to;
    // 发送用的数据类型
    unsigned short type;

    // 要发送的数据
    char const *data;
};

// 命令行参数解析函数，这里使用static关键字，是为了限制这个函数的作用域仅限于本文件。
static error_t parse_opt (int key, char *arg, struct argp_state *state){
  switch (key){}
  return 0;
}
static struct arguments const * parse_arguments(int argc, char *argv[]){
    // 这里声明了一个结构体数组
    struct argp_option option[] ={

    };

return NULL;
}
int main(int argc,char * argv[]){

}