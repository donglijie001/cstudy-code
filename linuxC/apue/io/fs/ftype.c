#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
static int ftype(const char * fname){
    struct stat statres;
    if (stat(fname, &statres)<0) {
        perror("stat()");
        exit(1);
    }
    /**
     * S_ISREG(m)  is it a regular file?

           S_ISDIR(m)  directory?

           S_ISCHR(m)  character device?

           S_ISBLK(m)  block device?

           S_ISFIFO(m) FIFO (named pipe)?

           S_ISLNK(m)  symbolic link?  (Not in POSIX.1-1996.)

           S_ISSOCK(m) socket?  (Not in POSIX.1-1996.)
     * 
     */
    if (S_ISREG(statres.st_mode)) {
        return '-';
    }else if (S_ISDIR(statres.st_mode)) {
        return 'd';
    }else if (S_ISCHR(statres.st_mode)) {
        return 'c';
    }else if (S_ISBLK(statres.st_mode)) {
        return 'b';
    }else {
        return '?';
    }
}
int main(int argc, char ** argv){
    if (argc<2) {
        fprintf(stderr, "Usage ... \n");
        exit(1);
    }
    printf("%c\n", ftype(argv[1]));
    exit(0);
}