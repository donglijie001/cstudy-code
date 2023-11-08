#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glob.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define DELIMS " \t\n"
struct cmd_st{
    glob_t globres;
};

static void prompt(){
//输出提示语句。
    printf("mysh-0.1$");
}
static void parse( char * line, struct cmd_st * res){
    char * tok;
    int i=0;
    while (1) {
       tok =  strsep(&line, DELIMS);
       if (tok==NULL) {
            break;
       }
       if (tok[0]=='\0') {
        // 如果是多个分割符，可能会解析出来一个空串
        // 比如 ls 后面跟两个空格，这个时候，就会解析出来空字符串。
        continue;
       }
       // 使用GLOB_NOCHECK，是为了不解析输入的tok，让它直接返回，这样就
       // 可以把tok给存起来，但是还有一个问题，只使用GLOB_NOCHECK 实际上
       // 是一个覆盖的作用，globres中只有一个结果，因此还需要用到GLOB_APPEND
       // 但是globres中的gl_pathc; 和gl_pathv里面的内容是随机的，因此就需要
       // 第一次不是append，后面的才是append, 使用i来设置，一开始i为0，所以
       // glob 第一次不执行追加，后续把i设为1，然后就执行追加。
       glob(tok, GLOB_NOCHECK | GLOB_APPEND*i,NULL, &(res->globres));
       i=1;
    }
    
}
int main(){
    char *linebuf = NULL;
    size_t linebuf_size =0;
    struct cmd_st cmd;
    while (1) {
        prompt();// 打印提示符
        if (getline(&linebuf, &linebuf_size,stdin)<0) {
            // 没有拿到数据，直接结束
            break;
        }
        parse(linebuf, &cmd);// 解析命令行
        if(0){ 

        }else {//是外部命令 // 二进程的可执行文件存在磁盘上就是外部命令，其他就是内部命令，比如进程消亡后的管理，就是内部命令。
           pid_t pid= fork();
            if(pid<0){
                perror("fork()");
                exit(1);
            }
            if(pid==0){// child
                execvp(cmd.globres.gl_pathv[0], cmd.globres.gl_pathv);
                perror("");
                exit(1);
            } else {
                wait(NULL);
            }
        }

    }

    exit(0);
}