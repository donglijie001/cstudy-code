#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
static void * func(void * p){
    puts("Thread is workding");
    return NULL;
}
int mian(){
    pthread_t tid;
    int err;
    puts("Begin!");
    err= pthread_create(&tid, NULL, func, NULL);
    if (err) {
        fprintf(stderr, "pthread_create():%s\n", strerror(err));
        exit(1);
    }
    puts("end");
    exit(0);
}