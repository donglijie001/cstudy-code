#include <stdio.h>
#include <stdlib.h>
#include <glob.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#define PAT "/etc"
int main(){
    DIR *dp;
    dp=opendir(PAT);
    struct dirent *cur;
    if (dp==NULL) {
        perror("opendir");
        exit(1);
    }
    while ((cur =readdir(dp))!=NULL) {
         puts(cur->d_name);
    }
    exit(0);
}