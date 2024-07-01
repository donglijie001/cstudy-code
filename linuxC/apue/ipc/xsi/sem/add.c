#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>
// 文件锁实例，多进程并发,往文件里写内容。
/**
 * 这里使用了信号量数组，父进程创建了消息队列，子进程就都知道了这个消息队列，
 所以可以创建一个进程私有的匿名消息队列IPC_PRIVATE
 * 
 */
#define  PROCNUM 20
#define  FANME "/tmp/out"
#define  LINESIZE 1024
static int semid;
static void P(void ){
    struct sembuf op;
    op.sem_num=0;
    op.sem_op=-1;
    op.sem_flg=0;
    while (semop(semid,&op,1)<0) {
        if (errno !=EINTR || errno !=EAGAIN) {
            perror("semop()");
            exit(1);
        }
    }
    
}
static void V(void){
    struct sembuf op;
    op.sem_num=0;
    op.sem_op=1;
    op.sem_flg=0;
    if (semop(semid,&op,1)<0) {
         perror("semop()");
            exit(1);
    }
}
// 打印出21，加了信号量，这样即使
static void  func_add(void){
    FILE * fp;
    fp = fopen(FANME, "r+");
    char linebuf[LINESIZE];
    if (fp==NULL) {
        // 打开文件失败，直接退出
        perror("fopen()");
        exit(1);
    }
    // 加上错误判断
    P();
    fgets(linebuf, LINESIZE,  fp);
    // 需要重新定位一下文件位置指针
    fseek(fp, 0, SEEK_SET);
    fprintf(fp, "%d\n", atoi(linebuf)+1); // fprintf是行缓冲模式，
    sleep(1);
    fflush(fp);// 刷新流。
    V();
    // 可能会导致文件意外解锁，在多进程环境下，多个进程都打开了这个文件，但是它们都卡在lock那一步
    // 这个时候应该先释放锁，然后再关闭，但是fprintf 是行缓冲的，在执行解锁的时候，可能没有把文件内容给写进去
    // 刷新缓冲区我觉得无论是行缓冲还是全缓冲都需要刷新。
    fclose(fp); 
}
int main(){
    int err;
    pid_t pid;
    semid= semget(IPC_PRIVATE, 1, 0600);
    if (semid<0) {
        perror("semget()");
        exit(1);
    }
    if(semctl(semid,0, SETVAL,1)<0){
        perror("semctl()");
        exit(1);
    }
    for(int i =0;i<PROCNUM;i++){
        pid = fork();
        if (pid<0) {
            fprintf(stderr, "fork()");
            exit(1);
        }
        if (pid==0) {
            func_add();
            exit(0);
        }
    }
    for (int i=0; i<PROCNUM; i++) {
        wait(NULL);
    }
    semctl(semid,0 ,IPC_RMID);
    exit(0);
}