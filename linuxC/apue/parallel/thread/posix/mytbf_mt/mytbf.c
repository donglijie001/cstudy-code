#include <assert.h>
#include <pthread.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include "mytbf.h"
struct mytbf_st* job[MYTBF_MAX];
static pthread_mutex_t mut_job= PTHREAD_MUTEX_INITIALIZER;
static pthread_t tid_alrm;
struct mytbf_st{
    int cps;
    int burst;
    int token;
    int pos;
    pthread_mutex_t mut;
    pthread_cond_t cond;
};
static pthread_once_t init_once = PTHREAD_ONCE_INIT;
static int get_free_pos_unlocked(void){
    // 加unlocked 后缀表示函数未加锁，但是访问之前要加锁。
    for (int i=0; i<MYTBF_MAX; i++) {
        if (job[i]==NULL) {
            return i;
        }
    }
    return -1;
}
static void * thr_alrm(void *p){
    // 给每个令牌桶申请token，同时判断是否超过阈值
    while (1) {
        pthread_mutex_lock(&mut_job);
        for (int i=0; i<MYTBF_MAX; i++) {
            if (job[i]!=NULL) {
                pthread_mutex_lock(&(job[i]->mut));
                job[i]->token += job[i]->cps;
                if (job[i]->token>job[i]->burst) {
                    job[i]->token = job[i]->burst;
                }
                pthread_cond_broadcast(&job[i]->cond);
                pthread_mutex_unlock(&(job[i]->mut));

            }
        }
        pthread_mutex_unlock(&mut_job);
        sleep(1);//  仅仅是测试用，应该用其他的函数代替
    }
    pthread_exit(NULL);
    

}
static void module_unload(void){
    pthread_cancel(tid_alrm);
    pthread_join(tid_alrm, NULL);
    for (int i=0; i<MYTBF_MAX; i++) {
        if (job[i]!=NULL) {
            mytbf_destory(job[i]);
        }
        
    }
    // 销毁互斥量
    pthread_mutex_destroy(&mut_job);
}
static void module_load(){


    int err = pthread_create(&tid_alrm  ,NULL, thr_alrm, NULL);
    if (err) {
            fprintf(stderr, "pthred_create():%s\n", strerror(err));
            exit(1);
        }
    // 注册一个钩子函数，退出时调用module_unload函数
    atexit(module_unload);
}
mytbf_t * mytbf_init(int cps, int burst){
    struct mytbf_st * me;
    pthread_once(&init_once ,module_load);

    me = malloc(sizeof(*me));
    if (me == NULL) {
        return NULL;
    }
    me->cps =cps;
    me->burst = burst;
    me->token =0;
    pthread_mutex_init(&(me->mut), NULL);
    pthread_cond_init(&(me->cond), NULL);

    pthread_mutex_lock(&mut_job);
    int pos= get_free_pos_unlocked();
    if (pos<0) {
        // 退出之前，要释放锁
        pthread_mutex_unlock(&mut_job);
        free(me);
        return NULL;
    }
    me->pos= pos;
    job[pos] = me;
    pthread_mutex_unlock(&mut_job);
    return me;
}
static int min(int a,int b){
    if (a<b) {
        return a;
    }
    return b;
}
int mytbf_fetchtoken(mytbf_t * ptr, int size){
    struct mytbf_st * me=ptr;
    if (size <=0) {
        // 返回errno ，这里返回负值
        return -EINVAL;
    }
    pthread_mutex_lock(&(me->mut));
    while (me->token <=0) {
        pthread_cond_wait(&(me->cond), &me->mut);
        // // 如果没有token就先释放锁，然后出让调度器，再加锁
        // pthread_mutex_unlock(&(me->mut));
        // sched_yield();
        // pthread_mutex_lock(&(me->mut));
    }
    // 有token以后，返回可以申请的数量。
    int n = min(me->token, size);
    me->token -= n;
    pthread_mutex_unlock(&(me->mut));


    return n;
}
int mytbf_returntoken(mytbf_t *ptr, int size){
    // 返回token这样写，应该是没有考虑到并发的情况。
    struct mytbf_st * me=ptr;

    if (size <=0) {
        //校验一下参数
        // 返回errno ，这里返回负值
        return -EINVAL;
    }
    pthread_mutex_lock(&(me->mut));
    me->token += size;
    if (me->token>me->burst) {
        me->token = me->burst;
    }
    pthread_cond_broadcast(&me->cond);

    pthread_mutex_unlock(&(me->mut));

    return size;
}
int mytbf_destory(mytbf_t *ptr){
    struct mytbf_st * me=ptr;
    pthread_mutex_lock(&mut_job);
    job[me->pos] = NULL;
    pthread_mutex_destroy(&(me->mut));
    pthread_cond_destroy(&me->cond);
    pthread_mutex_unlock(&mut_job);

    free(ptr);
    return 0;
}