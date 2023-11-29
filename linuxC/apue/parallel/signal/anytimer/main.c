#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "anytimer.h"
static void f1(void *p){
    char *str =p;
    printf("f1();%s\n", str);
}
static void f2(void *p){
    char *str =p;
    printf("f2();%s\n", str);
}
int main(){
    // 先打印Begin!End!，然后隔两秒打印bbb，再隔三秒打印aaa，再隔2秒打印ccc
    // Begin!End!..bbb...aaa..ccc........
    int job1,job2,job3;
    puts("Begin!");
    // 5秒钟之后调用f1
    job1=at_addjob(5, f1, "aaa");
    if (job1<=0) {
        fprintf(stderr, "at_addjob()%s\n", strerror(-job1));
        exit(1);
    }
    5,f1,"aaa"
    2,f2,"bbb"
    7,f1,"ccc"
    puts("End");

    while (1) {
        write(1, ".", 1);
        sleep(1);
    }

}