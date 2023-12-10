#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

#define  THRNUM 20
#define  FANME "/tmp/out"
#define  LINESIZE 1024
static pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
// 打印出21，加了信号量，这样即使
static void * thr_add(void * p){
    FILE * fp;
    fp = fopen(FANME, "r+");
    char linebuf[LINESIZE];
    if (fp==NULL) {
        // 打开文件失败，直接退出
        perror("fopen()");
        exit(1);
    }
    // 加锁
    pthread_mutex_lock(&mut);
    fgets(linebuf, LINESIZE,  fp);
    // 需要重新定位一下文件位置指针
    fseek(fp, 0, SEEK_SET);
    fprintf(fp, "%d\n", atoi(linebuf)+1);
    sleep(1);
    fclose(fp);
    // 释放锁
    pthread_mutex_unlock(&mut);

    pthread_exit(p);
}
int main(){
    pthread_t tid[THRNUM];
    int err;
    for(int i =0;i<THRNUM;i++){
        err = pthread_create(tid+i, NULL, thr_add, NULL);
        if (err) {
            fprintf(stderr, "pthread_create():%s\n", strerror(err));
            exit(1);
        }
    }
    for (int i=0; i<THRNUM; i++) {
        pthread_join(tid[i], NULL); 
    }
    pthread_mutex_destroy(&mut);
    exit(0);
}