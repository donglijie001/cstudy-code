#include <stdio.h>
#include <stdlib.h>
#include <glob.h>
#include <string.h>
#define PAT "/etc/a*.conf"
static int errfunc_(const char *epath, int eerrno){
    puts(epath);
    fprintf(stderr, "ERROR MSG:%s\n",strerror(eerrno));
    return 0;
}
int main(){
    // etc/a*.conf etc下以a开头的conf文件
    glob_t globres;
    int err, i;
    // errfunc 设置成了null，如果需要的话，就把errfunc_给写进去
    err=glob(PAT, 0, NULL, &globres);
    if (err!=0) {
        printf("Error code =%d,errMsg=%s\n", err, strerror(err));
        exit(1);
    }
    for ( i=0; i<globres.gl_pathc; i++) {
        puts(globres.gl_pathv[i]);
    }
    globfree(&globres);
    exit(0);
}