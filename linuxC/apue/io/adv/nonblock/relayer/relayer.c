#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <string.h>
#include "relayer.h"

#define BUFSIZE 1024
enum{
    STATE_R=1,
    STATE_W,
    STATE_Ex,// 异常
    STATE_T,//退出
};
struct rel_fsm_st{
    int state;
    int sfd;
    int dfd;
    int len;
    char buf[BUFSIZE];
    char * errstr;
    int pos;// 记录写入的位置，因为可能一次无法完全写入
    int64_t count;

};
struct rel_job_st{
    int job_state;
    int fd1;
    int fd2;
    struct rel_fsm_st fsm12, fsm21;
    int fd1_save,fd2_save;
};
static struct rel_job_st* rel_job[REL_JOBMAX];
static pthread_mutex_t mut_rel_job = PTHREAD_MUTEX_INITIALIZER;
static pthread_once_t init_once = PTHREAD_ONCE_INIT;

static void fsm_driver(struct rel_fsm_st * fsm){
    int ret;
    switch (fsm->state) {
        case STATE_R:
            fsm->len =read(fsm->sfd, fsm->buf, BUFSIZE);
            if (fsm->len==0) {
                fsm->state = STATE_T;
            }else if (fsm->len <0) {
                if (errno==EAGAIN) { //如果是假错，继续切换到读态
                 fsm->state = STATE_R;
                }else {
                fsm->errstr="read()";
                 fsm->state = STATE_Ex;
                }
            }else {
                fsm->pos=0;
                fsm->state = STATE_W;
            }
                break;
        case STATE_W:
           ret= write(fsm->dfd, fsm->buf+fsm->pos, fsm->len);
           if (ret<0) {
                if (errno==EAGAIN) { 
                 fsm->state = STATE_W;
                }else {
                fsm->errstr="write()";

                 fsm->state = STATE_Ex;
                }
           }else {
                fsm->pos+=ret;
                fsm->len -= ret;
                if (fsm->len==0) {
                    // 把数据全部读完了。
                    fsm->state=STATE_R;
                }else{
                    // 没有写完，继续写。
                    fsm->state = STATE_W;
                }
           }
                break;
        case STATE_Ex:
                perror(fsm->errstr);
                fsm->state=STATE_T;
                break;
        case STATE_T:
                // do somethging,因为这里是两个中端相互之间写来写去，所以暂时做不了啥
                break;
        default:
            abort();
            break;      
    }
}
static int get_free_pos_unlocked(){
    // unlocked 后缀表示访问这个函数需要加锁。
    for(int i =0;i<REL_JOBMAX;i++){
        if (rel_job[i]==NULL) {
            return i;
        }
    }
    return -1;
}
static void * thr_relayer(void * p){
    while (1) {
        pthread_mutex_lock(&mut_rel_job);
        for (int i=0; i<REL_JOBMAX; i++) {
           struct rel_job_st* job= rel_job[i];
            if (job !=NULL) {
                if (job->job_state == STATE_RUNNGING) {
                    fsm_driver(&job->fsm12);
                    fsm_driver(&job->fsm21);
                    if (job->fsm12.state==STATE_T&&job->fsm21.state==STATE_T) {
                        job->job_state= STATE_OVER;
                    }
                }
            }
        }
        pthread_mutex_unlock(&mut_rel_job);
    }
    return NULL;
    

}
static void module_unload(void ){

}
static void module_load(void){
    pthread_t tid_relayer;
    int err = pthread_create(&tid_relayer  ,NULL, thr_relayer, NULL);
    if (err) {
            fprintf(stderr, "pthred_create():%s\n", strerror(err));
            exit(1);
        }
    // 注册一个钩子函数，退出时调用module_unload函数
    atexit(module_unload);
}
int rel_addjob(int fd1, int fd2){
    struct rel_job_st * me;
    pthread_once(&init_once ,module_load);

    me=malloc(sizeof(*me));
    if (me==NULL) {
        return -ENOMEM;
    }
    me->fd1=fd1;
    me->fd2=fd2;
    me->job_state = STATE_RUNNGING;
    // 拿到fd1和fd2 文件描述符号的属性，
    me->fd1_save=fcntl(fd1, F_GETFL);
    me->fd2_save=fcntl(fd2, F_GETFL);
    //把fd1 和fd2设置成以非阻塞形式打开
    fcntl(fd1, F_SETFL, me->fd1_save| O_NONBLOCK);
    fcntl(fd2, F_SETFL, me->fd2_save| O_NONBLOCK);
    me->fsm12.sfd=me->fd1;
    me->fsm12.dfd=me->fd2;
    me->fsm12.state = STATE_R;

    me->fsm21.sfd=me->fd2;
    me->fsm21.dfd=me->fd1;
    me->fsm21.state = STATE_R;

    pthread_mutex_lock(&mut_rel_job);
    int pos = get_free_pos_unlocked();
    if (pos<0) {
        // 没有可用位置的话，就直接失败，但是失败之前，要释放锁，并把设置的一些状态进行恢复
        pthread_mutex_unlock(&mut_rel_job);
        fcntl(fd2, F_SETFL, me->fd2_save);
        fcntl(fd1, F_SETFL, me->fd1_save);
        free(me);
        return -ENOSPC;
    }
    
    rel_job[pos]= me;
    pthread_mutex_unlock(&mut_rel_job);
    
    return 0;
}

 #if 0
 int rel_canceljob(int fd1, int fd2);
/**
 * return   >=0 成功，指定任务成功取消
            == -EINVAL  失败，参数非法
            == -EBUSY  失败，任务早已被取消
 * 
 */
int rel_waitjob(int id, struct rel_stat_st *);
/**
 * @brief return ==0 成功，指定任务已终止并返回状态
                 == -EINVAL  失败，参数非法
 * 
 */
 int rel_statjob(int id, struct rel_stat_st *);
 /**
 * @brief return ==0 成功，指定任务状态已返回
                 == -EINVAL  失败，参数非法
 * 
 */
 #endif
