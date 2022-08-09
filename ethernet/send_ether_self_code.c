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
  // 首先从state中获取获取 用来存放解析后参数的arguemnts 结构体
  // 这里使用箭头获取struct state的值，是因为state 是一个结构体指针，所以访问其属性使用箭头，或者(*state).input 来代替，
  // 即对struct 变量进行访问使用的是点 ，而对struct指针进行访问使用的是
  struct arguments *arguments = state->input;

  switch (key){

  }
  return 0;
}
static struct arguments const * parse_arguments(int argc, char *argv[]){
    // 这里声明了一个结构体数组
    struct argp_option option[] ={
        // 网卡来源地址的命令行选项
         {"iface", 'i', "IFACE", 0, "name of iface for sending"},
         // 目的地址网卡的命令行选项
          {"to", 't', "TO", 0, "destination mac address"},

        // 发送数据类型的命令行选项
        {"type", 'T', "TYPE", 0, "data type"},

        // 发送数据的命令行选项 d是缩写
        {"data", 'd', "DATA", 0, "data to send"},
        // 空的终止记录
        { 0 }
    };

return NULL;
}
int main(int argc,char * argv[]){

}