#include <stdio.h>
#include <stdlib.h>
#define BUFSIZE 1024
/**
 * @brief 实现的类似cp的程序，接收三个参数。
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char ** argv){

    if (argc!=3) {
        fprintf(stderr, "Usage%s <src_file> <dest_file>\n",argv[0]);
        exit(1);
    }
    FILE * fps,*fpd;
    char buf[BUFSIZE];
    fps = fopen(argv[1], "r");
    if (fps==NULL) {
        perror("fopen()");
        exit(1);
    }
    fpd = fopen(argv[2], "w");
    if (fpd==NULL) {
        fclose(fps);
        perror("fopen()");
        exit(1);
    }
    int ch;
    int len=0;
    while ((len=fread(buf, 1,BUFSIZ, fps))>0) {
        fwrite(buf,1,len,fpd);
    }

    fclose(fpd);
    fclose(fps);

}