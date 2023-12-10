#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#define LEFT 30000000
#define RIGHT 30000200
#define THRNUM (RIGHT-LEFT) +1

static void * thr_prime(void * p){
    int mark=1;
    // 把i直接按地址传递进来，下面这行代码还没有执行，201个线程都指向同一个地址进行访问，就产生了竞争
    //int i = *(int *)p;
    int i = *(int *)p;
        for (int j =2; j<i/2; j++) {
            if (i%j==0) {
                mark=0;
                break;
            }
        }
        if (mark) {
            printf("%d is a primer\n", i);
        }
    pthread_exit(NULL);
}
int main(){

    int err,i;
    pthread_t tid[THRNUM];

    for (i=LEFT; i<=RIGHT; i++) {
        
        //err = pthread_create(tid+(i-LEFT), NULL, thr_prime, &i);
        err = pthread_create(tid+(i-LEFT), NULL, thr_prime, (void *)i);

        if (err) {
            fprintf(stderr, "pthred_create():%s\n", strerror(err));
            exit(1);
        }
    }
    for (i=LEFT; i<=RIGHT; i++) {
        pthread_join(tid[i-LEFT], NULL);
    }

    exit(0);
}