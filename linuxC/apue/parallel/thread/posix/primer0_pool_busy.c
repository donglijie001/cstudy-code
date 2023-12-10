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
// 这个版本，cpu占比比较高
static void * thr_prime(void * p){
    int mark;
    while (1) {
    
        pthread_mutex_lock(&mut_num);
        while (num==0) {
            pthread_mutex_unlock(&mut_num);
            sched_yield();// 出让调度器
            pthread_mutex_lock(&mut_num);
        }
        if (num==-1) {
            pthread_mutex_unlock(&mut_num); // 退出之前，一定要解锁，否则会导致死锁
            break;
        }
        int i = num;
        num =0;
        mark =1;
        pthread_mutex_unlock(&mut_num);
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
            // 先解锁，让其他线程有机会能读num，然后再加锁。
            pthread_mutex_unlock(&mut_num);
            sched_yield();// 出让调度器
            pthread_mutex_lock(&mut_num);
        }
        num =i;
        pthread_mutex_unlock(&mut_num);

    }
    pthread_mutex_lock(&mut_num);
    while (num!=0) {
            // 先解锁，让其他线程有机会能读num，然后再加锁。
            pthread_mutex_unlock(&mut_num);
            sched_yield();// 出让调度器
            pthread_mutex_lock(&mut_num);
    }
    num=-1;
    pthread_mutex_unlock(&mut_num);

    for (i=0; i<THRNUM; i++) {
        pthread_join(tid[i], NULL);
    }

    pthread_mutex_destroy(&mut_num);
    exit(0);
}