#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
// 文件锁实例，多进程并发,往文件里写内容。
#define  PROCNUM 20
#define  FANME "/tmp/out"
#define  LINESIZE 1024
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
    int fd= fileno(fp);
    // 加上错误判断
    lockf(fd, F_LOCK, 0);// 0表示文件有多长就锁多长
    fgets(linebuf, LINESIZE,  fp);
    // 需要重新定位一下文件位置指针
    fseek(fp, 0, SEEK_SET);
    fprintf(fp, "%d\n", atoi(linebuf)+1); // fprintf是行缓冲模式，
    sleep(1);
    fflush(fp);// 刷新流。
    lockf(fd, F_ULOCK, 0);
    // 可能会导致文件意外解锁，在多进程环境下，多个进程都打开了这个文件，但是它们都卡在lock那一步
    // 这个时候应该先释放锁，然后再关闭，但是fprintf 是行缓冲的，在执行解锁的时候，可能没有把文件内容给写进去
    // 刷新缓冲区我觉得无论是行缓冲还是全缓冲都需要刷新。
    fclose(fp); 
}
int main(){
    int err;
    pid_t pid;
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
    exit(0);
}