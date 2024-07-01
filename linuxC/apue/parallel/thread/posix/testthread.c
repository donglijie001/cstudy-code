#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
// 主要是想测试一下，子线程while true死等，会main线程先退出，子线程会退出吗
// 这里由于main线程退出，实际上整个进程就退出了，所以，main线程先退出，子线程也会退出
//https://blog.csdn.net/Luncles/article/details/132436950
// ps -eLf 可以查看创建的子线程
static void* func(void* p){
    // 休眠1000秒再退出
    sleep(1000);
    //return NULL;
    pthread_exit(NULL);// 退出线程，该方法可以进行线程栈的清理。
}
int main(){
    pthread_t tid;
    pthread_attr_t attr;
    int err;
    int i;
    pthread_attr_init(&attr);
    pthread_attr_setstacksize(&attr, 1024*1024);
    err= pthread_create(&tid, &attr, func, NULL);
    sleep(50);
    //exit(0);
}