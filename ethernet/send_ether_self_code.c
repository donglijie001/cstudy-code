#include <stdio.h>
#include <argp.h>

// 以太网的一些宏定义,定义成常量
#define MAX_ETHERNET_DATA_SIZE 1500

#define ETHERNET_HEADER_SIZE 14
#define ETHERNET_DST_ADDR_OFFSET 0
#define ETHERNET_SRC_ADDR_OFFSET 6
#define ETHERNET_TYPE_OFFSET 12
#define ETHERNET_DATA_OFFSET 14

#define MAC_BYTES 6
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
static error_t opt_handler (int key, char *arg, struct argp_state *state){
  // 首先从state中获取获取 用来存放解析后参数的arguemnts 结构体
  // 这里使用箭头获取struct state的值，是因为state 是一个结构体指针，所以访问其属性使用箭头，或者(*state).input 来代替，
  // 即对struct 变量进行访问使用的是点 ，而对struct指针进行访问使用的是箭头
  struct arguments *arguments = state->input;

  switch (key){
    case 'd':
            arguments->data = arg;
            break;
    case 'i':
            arguments->iface = arg; // 解析来源网卡
            break;
    case 't':
            arguments->to = arg;// 解析目的网卡
            break;
    case 'T':
            if (sscanf(arg, "%hx", &arguments->type) != 1) {
                return ARGP_ERR_UNKNOWN;
            }
            break;
    default:
            return ARGP_ERR_UNKNOWN;

  }
  return 0;
}
static struct arguments const * parse_arguments(int argc, char *argv[]){
  // docs for program and options
    static char const doc[] = "send_ether: send data through ethernet frame";
    static char const args_doc[] = "";

    // 这里声明了一个结构体数组
    static struct argp_option const options[] ={
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
    static struct argp const argp = {
        options,
        opt_handler,
        args_doc,
        doc,
        0,
        0,
        0,
    };
    static struct arguments arguments = {
        .iface = NULL,
        .to = NULL,
        //默认数据类型
        .type = 0x0900,
        // default data, 46 bytes string of 'a'
        // since for ethernet frame data is 46 bytes at least
        .data = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
    };

    argp_parse(&argp, argc, argv, 0, 0, &arguments);

    return &arguments;
}
/**
    将十六进制mac地址转成数字，a mac地址，类似："08:00:27:c8:04:83"，n 长度为6的数组，用来存放转换后的数字
*/
int mac_aton(const char *a, unsigned char *n){
    int matches =  sscanf(a, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx", n, n+1, n+2,
                         n+3, n+4, n+5);
    return (6 == matches ? 0 : -1);
}
int main(int argc,char * argv[]){
    // 解析参数
    struct arguments const *arguments=parse_arguments(argc,argv);
    if(arguments==NULL){
        printf("%s","Bad command line options given");
        return 1;
    }
    // 用来存放解析后的mac地址
    unsigned char to[6];
    int res = mac_aton(arguments->to, to);
    if (0 != res) {
        printf("Bad MAC address given: %s\n", arguments->to);
        return 2;
    }
    printf("%s\n", arguments->data);
    return 0;

}