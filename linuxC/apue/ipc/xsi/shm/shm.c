#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#define MEMSIZE 1024
int main(){

// 产生一个匿名IPC用于父子进程间通信。
    int shmid = shmget(IPC_PRIVATE,MEMSIZE ,0600);
    if (shmid<0) {
        perror("shmget()");
        exit(1);
    }
    pid_t pid;
    pid =fork();
    if (pid<0) {
        perror("fork()");
        exit(1);
    }
    void * ptr;
    if (pid ==0) { // child write
        ptr =shmat(shmid, NULL, 0);
        if (ptr ==(void *) -1) {
            perror("shmat()");
            exit(1);
        }
        strcpy(ptr, "Hello!");
        shmdt(ptr);
        exit(0);
    }else { // parent read
        wait(NULL);
        ptr =shmat(shmid, NULL, 0);
        if (ptr ==(void *) -1) {
            perror("shmat()");
            exit(1);
        }
        puts(ptr);
        shmdt(ptr);
        shmctl(shmid,IPC_RMID, NULL);
        exit(0);
    }
    

    
}