#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
extern char **environ;
/**
 * 实现date 
 * 
 * @return int 
 */
int main(){
    puts("Begin");
    // 刷新缓冲区
    fflush(NULL);
    // 传参从argv0开始传递
    execl("/bin/date", "date", "+%s", NULL);
    perror("execl()");
    exit(1);
    puts("End");
    exit(0);
}