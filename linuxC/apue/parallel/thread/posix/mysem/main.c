#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "mysem.h"
#define LEFT 30000000
#define RIGHT 30000200
#define THRNUM (RIGHT-LEFT) +1
#define N 4
static struct  mysem_t *sem;

static void * thr_prime(void * p){
    int mark=1;
    int i = (int)p;
        for (int j =2; j<i/2; j++) {
            if (i%j==0) {
                mark=0;
                break;
            }
        }
        if (mark) {
            printf("%d is a primer\n", i);
        }
    // 这个只是为了更方便观察现象
    sleep(5);
    mysem_add(sem,1);
    pthread_exit(NULL);
}
int main(){

    int err,i;
    pthread_t tid[THRNUM];

    sem=mysem_init(N);
    if (sem==NULL) {
        fprintf(stderr, "mysem_init failed!");
        exit(1);
    }

    for (i=LEFT; i<=RIGHT; i++) {
        
        mysem_sub(sem, 1);
        err = pthread_create(tid+(i-LEFT), NULL, thr_prime, (void *)i);

        if (err) {
            fprintf(stderr, "pthred_create():%s\n", strerror(err));
            exit(1);
        }
    }
    for (i=LEFT; i<=RIGHT; i++) {
        pthread_join(tid[i-LEFT], NULL);
    }

    mysem_destroy(sem);
    exit(0);
}