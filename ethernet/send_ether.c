#include <argp.h>
#include <stdio.h>
/**
 * struct for storing command line arguments.
 * 结构体用于存放解析结果
 **/
struct arguments {
    // name of iface through which data is sent
    char const *iface;
    // destination MAC address
    char const *to;

    // data type
    unsigned short type;

    // data to send
    char const *data;
};

static error_t opt_handler(int key, char *arg, struct argp_state *state) {
    // state 是参数解析的上下文，这里是把存放解析结果的结构体通过state给传递进来了。在解析参数的时候，把解析到的参数放到arguments里
    // 这里用的全部都是短选项，arguments->data = arg; 就是把解析到的结果给放到argument里，和我之前看到的argp的例子不太一样
    struct arguments *arguments = state->input;

    switch(key) {
        case 'd':
            arguments->data = arg;
            break;

        case 'i':
            arguments->iface = arg;
            break;

        case 'T':
            if (sscanf(arg, "%hx", &arguments->type) != 1) {
                return ARGP_ERR_UNKNOWN;
            }
            break;

        case 't':
            arguments->to = arg;
            break;

        default:
            return ARGP_ERR_UNKNOWN;
    }

    return 0;
}

/**
 * Parse command line arguments given by argc, argv.
 *
 *  Arguments
 *      argc: the same with main function.
 *
 *      argv: the same with main function.
 *
 *  Returns
 *      Pointer to struct arguments if success, NULL if error.
 **/
static struct arguments const *parse_arguments(int argc, char *argv[]) {
    // docs for program and options
    static char const doc[] = "send_ether: send data through ethernet frame";
    static char const args_doc[] = "";

    // command line options
    static struct argp_option const options[] = {
        // 第一个选项是命令行参数的长选项，第二个是参数的短选项，第三个选项 表示 该参数后面必须要跟一个 输入
        // Option -i --iface: name of iface through which data is sent
        {"iface", 'i', "IFACE", 0, "name of iface for sending"},

        // Option -t --to: destination MAC address
        {"to", 't', "TO", 0, "destination mac address"},

        // Option -T --type: data type
        {"type", 'T', "TYPE", 0, "data type"},

        // Option -d --data: data to send, optional since default value is set
        {"data", 'd', "DATA", 0, "data to send"},

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

    // for storing results
    static struct arguments arguments = {
        .iface = NULL,
        .to = NULL,
        //default data type: 0x0900
        .type = 0x0900,
        // default data, 46 bytes string of 'a'
        // since for ethernet frame data is 46 bytes at least
        .data = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
    };

    argp_parse(&argp, argc, argv, 0, 0, &arguments);

    return &arguments;
}
int main(int argc, char *argv[]){
    // parse command line options to struct arguments
    struct arguments const *arguments = parse_arguments(argc, argv);
    printf("data is:%s\n", arguments->data);
}
