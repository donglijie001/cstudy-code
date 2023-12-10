#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#define LEFT 30000000
#define RIGHT 30000200
#define THRNUM (RIGHT-LEFT) +1

struct thr_arg_st{
    int n;
};

static void * thr_prime(void * p){
    int mark=1;
    int i=((struct thr_arg_st * )p)->n;
   // free(p); 不太建议在这里释放内存。
        for (int j =2; j<i/2; j++) {
            if (i%j==0) {
                mark=0;
                break;
            }
        }
        if (mark) {
            printf("%d is a primer\n", i);
        }
    pthread_exit(p); // 把传递过来的地址给返回去。
}
int main(){

    int err,i;
    pthread_t tid[THRNUM];
    struct thr_arg_st * p;
    void * ptr;

    for (i=LEFT; i<=RIGHT; i++) {
        
        p = malloc(sizeof(*p));
        if (p==NULL) {
            perror("malloc(sizeof(*p))");
            exit(1);
        }
        p->n =i;
        err = pthread_create(tid+(i-LEFT), NULL, thr_prime, p);

        if (err) {
            fprintf(stderr, "pthred_create():%s\n", strerror(err));
            exit(1);
        }
    }
    for (i=LEFT; i<=RIGHT; i++) {
        pthread_join(tid[i-LEFT], &ptr); // 这里接收线程返回的地址，
        free(ptr);// 在这里释放创建线程时申请的内存
    }

    exit(0);
}