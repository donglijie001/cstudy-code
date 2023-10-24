#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(int argc,char ** argv){
    if (argc<2) {
     fprintf(stderr, "Usage...\n");
        exit(1);
    }
    FILE * fp;
    // 在声明指针的时候，一定要给变量设置初始值，否则会出现段错误。
    char * linebuf=NULL;
    //char * linebuf;
    size_t linesize=0;
    //size_t linesize;
    //printf("fopen before\n");
    fp= fopen(argv[1], "r");
    //printf("fopen after\n");

    if (fp==NULL) {
        perror("fopen()");
        exit(1);
    }
    while (1) {
        // 这里并没有把linebuf申请的内存给释放掉。
        //printf("getline before\n");

        if (getline(&linebuf, &linesize, fp)<0) {
            // 没有读到数据
            break;
        }
        //printf("getline after\n");

        printf("%s\n", linebuf);
        printf("%d\n", strlen(linebuf));
        printf("%d\n", linesize);

    }
    fclose(fp);
    exit(0);
}