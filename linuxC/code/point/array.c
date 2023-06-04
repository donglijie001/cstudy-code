#include <stdio.h>
#include <stdlib.h>
int main(){
    int a[3] = {1,2,3};
    int *p = a;
    int i;
    /*
        a[i] = *(a + i) = *(p + i) = p[i]
        &a[i] = a + i = p + i = &p[i]
        获取数组长度可以使用： sizeof(a)/sizeof(a[0]) 或者 sizeof(a)/sizeof(*a)
        p和a 都可以用来访问数组，它俩之间的区别，a是常量，p是变量，也就是a在初始化以后，
        就不能再赋值，但是p是可以赋值
    */
    for (i=0; i< sizeof(a)/sizeof(a[0]);  i ++) {
        //printf("%p ->%d \n",&a[i], a[i]);
       // printf("%p ->%d \n",a + i, a[i]);
         printf("%p ->%d \n",p + i, a[i]);
    }
    printf("\n");
    exit(0);
}