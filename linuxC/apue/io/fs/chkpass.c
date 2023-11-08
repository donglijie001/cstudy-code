#include <stdio.h>
#include <stdlib.h>
    char * input_pass;
    struct spwd *shadowline;
    if (argc<2) {
        fprintf(stderr, "Usage ...\n");
        exit(1);
    }
    // 获取密码
    input_pass= getpass("Password:")
    
}
