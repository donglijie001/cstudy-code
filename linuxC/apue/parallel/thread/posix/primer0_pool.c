#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#define LEFT 30000000
#define RIGHT 30000200
#define THRNUM 4
static int num=0; // 0 表示没有数据，-1 表示任务结束
static pthread_mutex_t mut_num = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond_num = PTHREAD_COND_INITIALIZER;

// 非盲等版本，cpu占用率低
static void * thr_prime(void * p){
    int mark;
    while (1) {
    
        pthread_mutex_lock(&mut_num);
        while (num==0) {
            pthread_cond_wait(&cond_num, &mut_num);
        }
        if (num==-1) {
            pthread_mutex_unlock(&mut_num); // 退出之前，一定要解锁，否则会导致死锁
            break;
        }
        int i = num;
        num =0;
        // 发广播
        pthread_cond_broadcast(&cond_num);
        pthread_mutex_unlock(&mut_num);
                mark =1;
            for (int j =2; j<i/2; j++) {
                if (i%j==0) {
                    mark=0;
                    break;
                }
            }
            if (mark) {
                printf("[%d]%d is a primer\n", (int)p,i);
            }
    }
    pthread_exit(NULL);
}
int main(){

    int err,i;
    pthread_t tid[THRNUM];

    for (i=0; i<THRNUM; i++) {
        err = pthread_create(tid+i, NULL, thr_prime, (void *)i);
        if (err) {
            fprintf(stderr, "pthred_create():%s\n", strerror(err));
            exit(1);
        }
    }
    for (i=LEFT; i<=RIGHT; i++) {
        pthread_mutex_lock(&mut_num);
        while (num!=0) {
            pthread_cond_wait(&cond_num, &mut_num);
        }
        num =i;
        // 叫醒任意一个线程就可以了
        pthread_cond_signal(&cond_num);
        pthread_mutex_unlock(&mut_num);

    }
    pthread_mutex_lock(&mut_num);
    while (num!=0) {
        pthread_cond_wait(&cond_num, &mut_num);
    }
    num=-1;
    pthread_cond_broadcast(&cond_num);
    pthread_mutex_unlock(&mut_num);

    for (i=0; i<THRNUM; i++) {
        pthread_join(tid[i], NULL);
    }

    pthread_mutex_destroy(&mut_num);
    pthread_cond_destroy(&cond_num);
    exit(0);
}