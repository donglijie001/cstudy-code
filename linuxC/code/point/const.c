#include <stdio.h>
#include <stdlib.h>
/**
 * const int a;
 * int const a;
 * const int *p; // 常量指针 ，指针指向的地址可以变化，但是指针指向的地址的值不可以变
   const 在星号前面，把*p看成一个值，const 一个值，就表示这个值不可以发生变化，
 * int const  *p; // 常量指针
 * int * const p; // 指针常量 指针指向的地址不能变，但是指针指向的地址的值可以变
 * const int * const p 指向的地址和指向的地址的值都不可以发生变化
 */
 #define PI 3.14
 // 2 * PI * r
 int main(){
    int i =1;
    int j=100;
    const int * const p =&i;

    printf("%d\n", *p);
    exit(0);
 }