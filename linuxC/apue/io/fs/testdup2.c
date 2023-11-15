#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <syslog.h>
#include <time.h>
int main(){
    // 关闭标准输出
    int fd = open("test1.txt", O_WRONLY|O_CREAT|O_TRUNC, 0600);
    // 输出重定向
    dup2(fd, STDOUT_FILENO);
    close(fd);
    close(STDOUT_FILENO);
    syslog(LOG_INFO, "testdup2 this is test%ld", time(NULL));
    fflush(NULL);
    exit(0);
}