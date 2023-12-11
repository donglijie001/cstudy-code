#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include "mysem.h"
struct mysem_st{
    int value;
    pthread_mutex_t mut;
    pthread_cond_t con;
};

mysem_t *mysem_init(int initval){
    struct mysem_st * me;
    me = malloc(sizeof(*me));
    if (me==NULL) {
        return NULL;
    }
    me->value = initval;
    pthread_mutex_init(&me->mut, NULL);
    pthread_cond_init(&me->con, NULL);
    return me;
}
int mysem_add(mysem_t * ptr, int n){
    struct mysem_st *me = ptr;
    pthread_mutex_lock(&me->mut);
    me->value+=n;
    pthread_cond_broadcast(&me->con);
    pthread_mutex_unlock(&me->mut);
    return n;
}
int mysem_sub(mysem_t *ptr, int n){
    if (n<=0) {
        return -1;
    }
    struct mysem_st *me = ptr;
    pthread_mutex_lock(&me->mut);
    while (me->value<n) {
        pthread_cond_wait(&me->con, &me->mut);
    }
    me->value -=n;
    pthread_mutex_unlock(&me->mut);
    return n;
}
int mysem_destroy(mysem_t * ptr){
    struct mysem_st *me = ptr;
    pthread_mutex_destroy(&me->mut);
    pthread_cond_destroy(&me->con);
    free(me);
    return 0;
}