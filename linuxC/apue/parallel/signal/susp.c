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
   sigprocmask(SIG_BLOCK, &set, &oset);
    for (int j=0 ; j<1000; j++) {
        //先阻塞住
         for (i=0; i<5; i++) {
             write(1, "*", 1);
             sleep(1);
        }   
        write(1, "\n", 1);
        // 解除信号集的阻塞，并马上进入到等待信号阶段
        sigsuspend(&oset);// 这一行的作用，就等于下面几行代码，是一个原子化的操作。
        /*
        首先for 循环外面先block住信号，打印完星号后，下面这几行代码，先恢复oset，
        然后把原来的状态给保存到tmpset，然后调用pause，等待信号，信号处理完以后，再把tmpset给恢复
        sigset_t tmpset; // tmpset 和set是一样的
        sigprocmask(SIG_SETMASK, &oset, &tmpset);
        pause();
        sigprocmask(SIG_SETMASK, &tmpset, NULL);
        */

    }
    sigprocmask(SIG_SETMASK, &saveset, NULL);
   
    exit(0);
}