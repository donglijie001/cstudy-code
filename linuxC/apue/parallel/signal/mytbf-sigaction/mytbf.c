#include <assert.h>
#include <signal.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/time.h>
#include "mytbf.h"
typedef void (*sighandler_t)(int);
struct mytbf_st* job[MYTBF_MAX];
static volatile int inited =0;
static struct sigaction alrm_sa_save;
struct mytbf_st{
    int cps;
    int burst;
    int token;
    int pos;
};
static int get_free_pos(void){
    for (int i=0; i<MYTBF_MAX; i++) {
        if (job[i]==NULL) {
            return i;
        }
    }
    return -1;
}
static void alrm_action(int s, siginfo_t * infop, void * unused){    
    if (infop->si_code!=SI_KERNEL) {
        // 如果信号不是来自kernel，就忽略
        return;
    }
// 给每个令牌桶申请token，同时判断是否超过阈值
    for (int i=0; i<MYTBF_MAX; i++) {
        if (job[i]!=NULL) {
            job[i]->token += job[i]->cps;
            if (job[i]->token>job[i]->burst) {
                job[i]->token = job[i]->burst;
            }
        }
    }

}
static void module_unload(void){
    
     //取消当前尚未完成的计时器
    struct itimerval itv;
    itv.it_interval.tv_sec =0;
    itv.it_interval.tv_usec=0;
    itv.it_value.tv_sec =0;
    itv.it_value.tv_usec =0;
    setitimer(ITIMER_REAL, &itv, NULL);
    // 恢复之前的信号处理程序
    sigaction(SIGALRM, &alrm_sa_save, NULL);

    for (int i=0; i<MYTBF_MAX; i++) {
        free(job[i]);
    }
}
static void module_load(){
  struct sigaction sa;
  struct itimerval itv;
  sa.sa_sigaction = alrm_action;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags =SA_SIGINFO;// 加上这行表示使用sa_sigaction 而不是handler。
  sigaction(SIGALRM, &sa, &alrm_sa_save);
  //sigaction 加上erro判断
    itv.it_interval.tv_sec =1;
    itv.it_interval.tv_usec=0;
    itv.it_value.tv_sec =1;
    itv.it_value.tv_usec =0;
 
  setitimer(ITIMER_REAL, &itv, NULL);
  // setitimer加上错误判断。

// 注册一个钩子函数，退出时调用module_unload函数
    atexit(module_unload);

}
mytbf_t * mytbf_init(int cps, int burst){
    struct mytbf_st * me;
    if (!inited) {
        //这个逻辑目的就是让signal只执行一次，所以加了一个inited变量，
        //执行完把它置为1，这样就不会再重复执行了，不过貌似没有考虑并发的场景。
        module_load();// 给信号注册行为，并发出第一个alarm信号
        inited=1;
    }
    int pos= get_free_pos();
    if (pos<0) {
        //存放令牌桶的结构体指针没有空位置。直接返回NULL
        return NULL;
    }
    me = malloc(sizeof(*me));
    if (me == NULL) {
        return NULL;
    }
    me->cps =cps;
    me->burst = burst;
    me->token =0;
    me->pos= pos;
    job[pos] = me;

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
    while (me->token <=0) {
        // 如果没有token就休眠等待，这里加while，是因为被唤醒的时候不一定有token。
        pause();
    }
    // 有token以后，返回可以申请的数量。
    int n = min(me->token, size);
    me->token -= n;
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
    me->token += size;
    if (me->token>me->burst) {
        me->token = me->burst;
    }
    return size;
}
int mytbf_destory(mytbf_t *ptr){
    struct mytbf_st * me=ptr;
    job[me->pos] = NULL;
    free(ptr);
    return 0;
}