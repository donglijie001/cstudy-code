#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "anytimer.h"
struct anytimer_st{
    int sec;
    void * func;
    void * arg;
    int flag; // 标识这个job的状态，0表示正常，非1表示结束。
};
struct anytimer_st * anytimer_arr[ANYTIMER_MAX];
static int get_free_pos(){
    // 获取第一个
    for(int i =0;i<ANYTIMER_MAX;i++){
        if (anytimer_arr[i]==NULL) {
            return i;
        }
    }
    return -1;
}

int at_addjob(int stc, at_jobfunc_t* jobp, void * arg){
    if (jobp==NULL || arg == NULL) {
        //参数非法
       return  -EINVAL;
    }
    int index =get_free_pos();
    struct anytimer_st * me;
    me = malloc(sizeof(*me));
    if (me==NULL) {
        return -ENOMEM;
    }
    me->arg= arg;
    me-


}