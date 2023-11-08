#include <stdio.h>
#include <stdlib.h>
#include <glob.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#define PAT "/etc"
#define PAT1 "/home/donglijie/cstudy-code/linuxC"


int main(){
    DIR *dp, *dp1;
    dp=opendir(PAT);
    struct dirent *cur;
    if (dp==NULL) {
        perror("opendir");
        exit(1);
    }
    //1
    cur =readdir(dp);
    puts(cur->d_name);
    //2
    cur =readdir(dp);
    puts(cur->d_name);
    //3
    cur =readdir(dp);
    puts(cur->d_name);
    //4
    cur =readdir(dp);
    //5
    puts(cur->d_name);
    dp1=opendir(PAT1);
    printf("after read new dir");
    cur =readdir(dp);
    puts(cur->d_name);
    cur =readdir(dp);
    puts(cur->d_name);
    cur =readdir(dp);
    puts(cur->d_name);
    cur =readdir(dp);
    puts(cur->d_name);
    exit(0);
}