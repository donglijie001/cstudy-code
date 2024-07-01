#ifndef RELAYER_H__
#define RELAYER_H__
#include <stdint.h>
#define REL_JOBMAX 10000
enum{
    STATE_RUNNGING =1,
    STATE_CANCELED,
    STATE_OVER
};
// 这个只是为了让用户看到，实际上并不能完整的描述一个job
struct rel_stat_st{
    int state;
    int fd1;
    int fd2;
    int64_t count12; // 1对2 说了多少话
    int64_t count21;
};
int rel_addjob(int fd1, int fd2);
/**
 * return   >=0 成功，返回当前任务ID
            == -EINVAL  失败，参数非法
            == -ENOSPC  失败，内存数组满
            == -ENOMEM 失败，内存分配有误
 * 
 */
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