#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
int main(){
    // 以只读形式打开文件
    FILE * fp = fopen("tmp1", "r");
    if (fp==NULL) {
        //fprintf(stderr, "open error, errno:%d\n", errno);
        // 这里用perror更好
        perror("fopen()");
        exit(1);
    }
}