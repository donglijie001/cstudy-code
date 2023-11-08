#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define LEFT 30000000
#define RIGHT 30000200
int main(){
    pid_t pid;
    for (int i=LEFT; i<=RIGHT; i++) {
        int mark=1;
        // 创建一个新的进程
        pid = fork();
        if (pid<0) {
            // 创建进程失败，直接结束。
            perror("fork()");
            exit(1);
        }else if (pid ==0) {
            // 子进程
            for (int j =2; j<i/2; j++) {
                if (i%j==0) {
                    mark=0;
                    break;
                }
            }
            if (mark) {
                printf("%d is a primer\n", i);
            }
        
            exit(0);
        }
    
    }
    // int st;
    for (int i=LEFT; i<=RIGHT; i++) {
        wait(NULL);
    }
    exit(0);
}