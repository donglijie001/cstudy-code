#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <syslog.h>
#include <string.h>
#include <errno.h>
#define FNAME "/tmp/out"
static int  daemonize(){
    int fd;
    pid_t pid = fork();
    if (pid<0) {
        //perror("fork()");
        return -1;;
    }
    if (pid>0) {// parent
        exit(0);
    }
    // 进程默认打开的文件描述符0 1 2 就不需要打开了，因此先进行重定向。
    fd = open("/dev/null",O_RDWR);
    if (fd<0) {
       // perror("open()");
        return -1;
    }
    // 标准输入、输出、出错重定向到fd
    dup2(fd, 0);
    dup2(fd, 1);
    dup2(fd, 2);
    if (fd>2) {
        // 关闭fd
        close(fd);
    }
    setsid(); // 设置守护进程
    // 把当前工作路径设置为根路径，如果守护进程是在某个设备上工作
    // 如果设备umount可能会出问题，所以需要修改工作路径
    chdir("/"); 
    // 如果确定后续不会在产生文件，可以执行umask(0)
    // umask(0)
    return 0;

}
int main(){
    FILE * fp;
    openlog("mydaemon", LOG_PID, LOG_DAEMON);
    if (daemonize()) {
        // 失败了就直接结束
        //exit(1);
        syslog(LOG_ERR, "daemonize() failed");
    }else {
        syslog(LOG_INFO, "daemonize() successed!");
    }
    fp = fopen(FNAME, "w");
    if (fp==NULL) {
        //perror("fopen()");
        syslog(LOG_ERR, "fopen:%s", strerror(errno));
        exit(1);
    }
    syslog(LOG_INFO, "%s was opened.", FNAME);

    for (int i=0; i<1000; i++) {
        fprintf(fp, "%d\n", i);
        fflush(fp);
        syslog(LOG_DEBUG, "%d is printed.", i);

        sleep(1);
    }
    // 不会执行到。
    fclose(fp);
    exit(0);
}