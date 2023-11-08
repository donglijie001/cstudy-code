#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <glob.h>
#define PATHSIZE 1024
static int path_noloop(const char * path){
    char * pos;

    // 找到最右边的/,比如/a/b/c ,pos的结果就是 /c, 如果是隐藏目录，比如/a/.，返回的就是 /.
    pos = strrchr(path, '/');
    if (pos==NULL) {
        exit(1);
    }
    if (strcmp(pos+1, ".")==0|| strcmp(pos+1, "..")==0) {
        return 0;
    }
    return 1;
}
static int64_t mydu(const char * path){
    static struct stat statres; // 加上static， 变量就不会存在栈里，而是存在静态区，
    //这样就可以优化单次循环的所占的栈空间的大小，
    // 如果一个变量没有横跨递归点来使用（比如只在递归点之前，或者递归点之后），就可以把这个变量放到静态区去使用
    // 比如statres和nextpath 没有横跨递归点，所以可以把它放到静态区。
    
    static char nextpath[PATHSIZE];
    glob_t globres;
    
    printf("%s\n", path);

    if (lstat(path, &statres)<0) {
        perror("lstat()");
        exit(1);
    }
    if (!S_ISDIR(statres.st_mode)) {
        int64_t size= sizeof(statres.st_blocks);
        return statres.st_blocks;
    }
    //加上当前目录的size
    int64_t sum=statres.st_blocks;
    strncpy(nextpath,path, PATHSIZE);
    strncat(nextpath,"/*", PATHSIZE);
    glob(nextpath, 0, NULL,&globres);
    strncpy(nextpath,path, PATHSIZE);
    strncat(nextpath,"/.*", PATHSIZE);
    glob(nextpath, GLOB_APPEND, NULL,&globres);
    for ( int i=0; i<globres.gl_pathc; i++) {
        // 需要判断是否是.或者..目录，这个时候再进行判断，会陷入死循环
        if (path_noloop(globres.gl_pathv[i])) {
            sum +=mydu(globres.gl_pathv[i]);
        }
        
    }
    // 释放资源
    globfree(&globres);
    return sum;
}
int main(int argc,char ** argv){
    if (argc<2) {
        fprintf(stderr, "Usage ... \n");
        exit(1);
    }
    int64_t size= mydu(argv[1]);
    printf("%lld\n",size/2);
    exit(0);

}