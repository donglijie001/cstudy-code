#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
// 求一个文件中有多少个字符a
int main(int argc, char *argv[]){
    char * str;
    if (argc<2) {
        fprintf(stderr, "Usage...\n");
        exit(1);
    }
    int fd =open(argv[1], O_RDONLY);
    if (fd<0) {
        perror("open()");
        exit(1);
    }
    struct stat statres;
    if (fstat(fd, &statres)<0) {
        perror("fstat()");
        exit(1);
    }
    str =mmap(NULL,statres.st_size, PROT_READ, MAP_SHARED, fd, 0);
    if (str==MAP_FAILED) {
        perror("mmap()");
        exit(1);
    }
    close(fd);
    int count=0;
    for(int i=0;i<statres.st_size;i++){
        if (str[i]=='a') {
            count++;
        }
    }
    printf("%d\n", count);
    


    munmap(str, statres.st_size);


    exit(0);
}