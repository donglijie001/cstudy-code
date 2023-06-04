#include <stdio.h>
#include <stdlib.h>
int main(){
    int a[2][3] = {1,2,3,4,5,6};
    int i,j;
    //以下是二维数组的输出
    #if 0
    for (i=0; i< 2;  i ++) {
         for (j=0; j<3 ;j++) {
            printf("%d ",a[i][j]);
         }
         printf("\n");
    }
    #endif
    /* a 是行指针，a + 1 是跳过一行,下面是验证代码，并且声明一个指针让 
    它指向数组首元素的地址，有两种方式 p = *(a+i) + j;或 p = &a[i][j]
    特别的是数组首元素的地址：p = *a; p = &a[0][0]，这里p指针是当作一个列指针。
    */
    int *p;
    p = *a;// p = &a[0][0]
    printf("%p %p\n",a, a + 1);
    printf("%p %p\n",p, &a[0][0]);

    for (i=0; i< 2;  i ++) {
         for (j=0; j<3 ;j++) {
            printf("%p -> %d\n",&a[i][j],a[i][j]);
         }
         printf("\n");
    }

    int  (*q)[3]= a;
    exit(0);
}