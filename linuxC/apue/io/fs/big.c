#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main(int argc, char **argv){
    if (argc<2) {
        fprintf(stderr, "Usage ... \n");
        exit(1);
    }
   int  fd = open(argv[1], O_WRONLY | O_CREAT|O_TRUNC,0600);
   if (fd <0) {
    perror("open()");
    exit(1);
   }
   // 应该判断lseek的返回值，会有整型溢出，把变量提升为long型
   lseek(fd,5LL*1024*1024*1024-1, SEEK_SET);
   write(fd, "", 1);
   close(fd);
   exit(0);
}