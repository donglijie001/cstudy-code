#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define  FNAME "/tmp/out"
int main(){
    // 把hello 输出到某个文件里。
    int fd;
    fd =open(FNAME,O_WRONLY|O_TRUNC|O_CREAT,0600);
    if (fd<0) {
        perror("open()");
        exit(1);
    }
    // close(1);
    // dup(fd);
    // 这上面两行，不是原子化操作，是有问题的。
    dup2(fd, 1);
    if (fd!=1) {
        close(fd);
    }
// 往标准输出里输出hello
    puts("hello!");
    exit(0);
}