#include <stdio.h>
#include <stdlib.h>
int add(int a,int b){
    return a +b;
}
int main(){
    int a=3,b=5;
    int ret;
    // 定义一个函数指针
    int (*p)(int,int); 
    //ret =add(a,b);
    p = add;
    ret =p(a,b);
    int (* funcp[1])(int ,int);
    funcp[0] = add;
    ret = funcp[0](a,b);
    printf("%d\n", ret);

    exit(0);
}