#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
// 测试一下一个进程到底可以创建多少个线程，没有进行任何特殊设置的情况
//,我在32位的虚拟机上运行了一下，381个线程
static void* func(void* p){
    puts("Thread is working");
    //return NULL;
    pthread_exit(NULL);// 退出线程，该方法可以进行线程栈的清理。
}
int main(){
    pthread_t tid;
    pthread_attr_t attr;
    int err;
    int i;
    pthread_attr_init(&attr);
    pthread_attr_setstacksize(&attr, 1024*1024);

    puts("Begin!");
    for (i=0; ; i++) {
        err= pthread_create(&tid, &attr, func, NULL);
        if (err) {
            fprintf(stderr, "pthread_create():%s\n", strerror(err));
            break;
        }
    }
    printf("%d\n",i);
    pthread_attr_destroy(&attr);
    exit(0);
}