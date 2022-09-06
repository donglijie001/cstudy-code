#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
// 要引入下面这个。bool 是在c99中才有的，所以要引入下面这个头文件
#include <stdbool.h> 
#include <libgen.h>
static bool stop = false;
static void handle_term(int sig){
    stop = true;
}
int main(int argc, char* argv[]){
    signal(SIGTERM, handle_term);
    if (argc <=3) {
        printf("useage: %s ip_address port_number backlog\n", basename(argv[0]));
    }
}