#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
static void* func(void* p){
    puts("Thread is working");
    return NULL;
    
}
int main(){
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