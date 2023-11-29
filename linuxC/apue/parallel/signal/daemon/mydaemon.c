#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/syslog.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <syslog.h>
#include <string.h>
#include <errno.h>
#define FNAME "/tmp/out"
static   FILE * fp;
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
static void daemon_exit(){
    fclose(fp);
    closelog();
    exit(0); // 进程变成正常终止了，这句话不太理解
}
int main(){

    /*
     注册了多个信号，执行相同的信号处理函数，daemon_exit 是会有重入的危险，比如第一个信号来了刚执行完fclose，
     然后另外一个信号来了，又执行了一遍fclose。会有问题，在这里，期望是响应一个信号的时候，先把另外的信号给block住。
    */
    // signal(SIGINT, daemon_exit);
    // signal(SIGQUIT, daemon_exit);
    // signal(SIGTERM, daemon_exit);
    // 上面的三行代码有重入的风险。
    struct sigaction sa;
    sa.sa_handler = daemon_exit;
    sigemptyset(&sa.sa_mask);
    // 设置处理信号的时候的忽略信号。
    sigaddset(&sa.sa_mask, SIGQUIT);
    sigaddset(&sa.sa_mask, SIGTERM);
    sigaddset(&sa.sa_mask, SIGINT);
    sa.sa_flags =0;
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGQUIT, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);
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