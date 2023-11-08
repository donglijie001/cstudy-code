#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h>
int main(int argc, char ** argv){
    if (argc<2) {
        fprintf(stderr, "Usage ...\n");
        exit(1);
    }

    struct passwd * pwdlinde;

    pwdlinde= getpwuid(atoi(argv[1]));
    puts(pwdlinde->pw_name);

    exit(0);
}