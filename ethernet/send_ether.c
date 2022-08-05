#include <argp.h>
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


int main(int argc, char *argv[]);