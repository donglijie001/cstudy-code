#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
static void cleanup_func(void *p){
    puts(p);
}
static void* func(void* p){
    puts("Thread is working");
    pthread_cleanup_push(cleanup_func,"cleanup:1");
    pthread_cleanup_push(cleanup_func,"cleanup:2");
    pthread_cleanup_push(cleanup_func,"cleanup:3");

    puts("push over!");
    pthread_cleanup_pop(1);//真表示执行。
    pthread_cleanup_pop(1);
    pthread_cleanup_pop(1);
    

    pthread_exit(NULL);// 退出线程，该方法可以进行线程栈的清理。
}
int main(){

    pthread_t tid;

    puts("Begin!");
    int err;
    puts("Begin!");
    err= pthread_create(&tid, NULL, func, NULL);
    if (err) {
        fprintf(stderr, "pthread_create():%s\n", strerror(err));
        exit(1);
    }
    pthread_join(tid, NULL);
    puts("End!");
    exit(0);
}