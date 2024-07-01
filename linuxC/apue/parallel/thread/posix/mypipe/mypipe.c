#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "mypipe.h"
struct mypipe_st{
    int head;
    int tail;
    char data[PIPESIZE];
    int datasize;
    int count_rd;
    int count_wr;
    pthread_mutex_t mut;
    pthread_cond_t cond;

};
mypipe_t * mypipe_init(void){
    struct mypipe_st * me;
    me = malloc(sizeof(*me));
    if (me==NULL) {
        return NULL;
    }
    me->head=0;
    me->tail=0;
    me->datasize=0;
    pthread_mutex_init(&me->mut, NULL);
    pthread_cond_init(&me->cond, NULL);
    return me;
}
// mypipe_unregister 和mypipe_register 并么有考虑到就是欺骗系统的行为，即注册为读者，
// 但是不执行读的操作，然后mypipe_unregister 时候，以写者进行注销
int mypipe_unregister(mypipe_t *ptr , int opmap){
    /** 应该有一个判断，就是最低位或者次低位不为就直接失败*/
    struct mypipe_st * me =ptr;
    pthread_mutex_lock(&me->mut);
    if (opmap&MYPIPE_READ) {
        me->count_rd--;
    }
    if (opmap&MYPIPE_WRITE) {
        me->count_wr--;
    }
    //unregister的时候，有可能有写者或者读者在等待，所以要发一个广播
    pthread_cond_broadcast(&me->cond);
    pthread_mutex_unlock(&me->mut);
    return 0;
}

int mypipe_register(mypipe_t * ptr, int opmap){
     struct mypipe_st * me =ptr;
    /** 应该有一个判断，就是最低位或者次低位不为就直接失败*/
    pthread_mutex_lock(&me->mut);

    if (opmap&MYPIPE_READ) {
        me->count_rd++;
    }
    if (opmap&MYPIPE_WRITE) {
        me->count_wr++;
    }
    while (me->count_rd<=0|| me->count_wr<=0) {
        pthread_cond_wait(&me->cond, &me->mut);
    }
    // 发广播，告诉其他注册身份的人，看是否
    pthread_cond_broadcast(&me->cond);

    pthread_mutex_unlock(&me->mut);
    return 0;
}
static int mypipe_read_byte_unlocked(struct mypipe_st *me, char * datap){
    if(me->datasize<=0){
        return -1;
    }
    *datap = me->data[me->head];
    me->head = next(me->head);
    me->datasize--;
    return 0;
}
int mypipe_read(mypipe_t * ptr, void * buf, size_t count){
    struct mypipe_st * me =ptr;
    pthread_mutex_lock(&me->mut);

    while (me->datasize<=0 && me->count_wr>0) {
        // 当前管道空，并且有写者才等待，否者就直接结束
        pthread_cond_wait(&me->cond, &me->mut);
    }
    if (me->datasize<=0 && me->count_wr<=0) {
        // 管道空，没有写者直接退出了
        pthread_mutex_unlock(&me->mut);
        return 0;
    }
    int i=0;
    for (i=0; i<count; i++) {
        if(mypipe_read_byte_unlocked(me, buf+i)!=0){
            // 读失败，直接返回
            break;
        }
    }
    // 发广播，告诉其他写者可以写数据了。
    pthread_cond_broadcast(&me->cond);
    pthread_mutex_unlock(&me->mut);
    return i;
}
int mypipe_write(mypipe_t * ,const void * buf, size_t size);

int mypipe_destory(mypipe_t * ptr){
    struct mypipe_st * me =ptr;
    pthread_mutex_destroy(&me->mut);
    pthread_cond_destroy(&me->cond);
    free(ptr);
    return 0;
}