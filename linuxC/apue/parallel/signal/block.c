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
    sigset_t set,oset,saveset;
    signal(SIGINT, int_handler);
    sigemptyset(&set);// 置成空集
    sigaddset(&set, SIGINT);// 添加一个中断信号
    // 通过for 循环外面的sigprocmask 保证了经过这段程序信号的状态不会发生改变。
    sigprocmask(SIG_UNBLOCK, &set, &saveset);

    for (int j=0 ; j<1000; j++) {
        //先阻塞住
        sigprocmask(SIG_BLOCK, &set, NULL);
         for (i=0; i<5; i++) {
             write(1, "*", 1);
             sleep(1);
        }   
        write(1, "\n", 1);
        sigprocmask(SIG_UNBLOCK, &set, NULL);
    }
    sigprocmask(SIG_SETMASK, &saveset, NULL);
   
    exit(0);
}