#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#define MEMSIZE 1024
/**
 * 共享内存的例，先mmap，在父进程里映射了一下内存，然后fork一个子进程，这样子进程里
 也映射了内存，然后子进程往共享内存里写数据，父进程从里读，
 *
 * @return int 
 */
int main(){
    char * ptr;
    pid_t pid;
    // 没有使用到文件所以fd是-1，length是0
    ptr=mmap(NULL,MEMSIZE,PROT_READ | PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS, -1,0);
    if (ptr==MAP_FAILED) {
        perror("mmap()");
        exit(1);
    }
    pid =fork();
    if (pid<0) { // 创建子进程失败
        perror("fork()");
        munmap(ptr, MEMSIZE);
        exit(1);
    }
    if (pid==0) {// child write
        strcpy(ptr,"Hello!");
        munmap(ptr, MEMSIZE);
        exit(0);
    }else { //父进程
        wait(NULL);//等待子进程执行完
        puts(ptr);
        munmap(ptr, MEMSIZE);
        exit(0);
    }
}