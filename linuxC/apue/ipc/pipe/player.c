#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
// 使用mpg123 播放音乐伪码
int main(){
    int pd[2];
    pid_t pid;
    int len;
    char buf[BUFSIZ];
    if (pipe(pd)<0) {
        perror("pipe()");
        exit(1);
    }
    pid = fork();
    if (pid<0) {
        perror("fork()");
        exit(1);
    }
    if (pid==0) {//child read
        close(pd[1]);//关闭写端
        dup2(pd[0], 0);
        close(pd[0]);
        int fd=open("dev/null", O_RDWR);
        dup2(fd, 1);
        dup2(fd,2);
        execl("/usr/bin/mpg123", "mpg123", "-", NULL);
        perror("execl()");
        exit(1);
    }else { // parent write
        close(pd[0]);//关闭读
        // 父进程从网上收数据，往管道中写
        close(pd[1]);
        wait(NULL);
        exit(0);
    }
}