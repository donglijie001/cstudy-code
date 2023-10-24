#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/**
 * 使用系统IO实现cp 这个命令
 * 
 */
int main(int argc,char ** argv){
    // 1、校验输入的参数，是否符合预期，主要是校验参数个数
    if (argc !=3) {
        // 这里不用perror，是因为，这个时候，并没有报错，errno并不是特定的错误码
        fprintf(stderr, "Usage%s <src_file> <dest_file>\n",argv[0]);
        exit(1);
    }
    // 2、 打开源文件，以只读的形式打开
   int fds= open(argv[1], O_RDONLY);
    
}