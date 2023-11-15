#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
static void int_handler(int s){
    // 参数s的含义后面再说。
    write(1, "!", 1);
}
int main(){
    int i;
    // singal 除了接受函数指针外，还可以接特定的信号： SIG_IGN, SIG_DFL
    //signal(SIGINT, SIG_IGN);
    signal(SIGINT, int_handler);
    for (i=0; i<10; i++) {
        write(1, "*", 1);
        sleep(1);
    }
    exit(0);
}