#include <argp.h>
/**
 * struct for storing command line arguments.
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