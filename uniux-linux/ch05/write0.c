#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
int main(int ac, char * av[]){
    int fd;
    char buf[BUFSIZ];
    if (ac !=2) {
        fprintf(stderr, "usage: write0 ttyname\n");
        exit(1);
    }
    fd = open(av[1], O_WRONLY);
    if (fd==-1) {
        perror(av[1]);
        exit(1);
    }
    while (fgets(buf, BUFSIZ,  stdin) !=NULL) { // 从终端获取输入信息
        if (write(fd,buf,strlen(buf)) ==-1) { // 输出信息到另一个终端
            break; 
        }
    }
    close(fd);
}