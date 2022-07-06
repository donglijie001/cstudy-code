#include <stdio.h>
#include<string.h>
int main(void){
    // printf("Helllo World\n");
    // printf("%zd\n", sizeof(int));
    // int x = 1;
    // printf("x's address is %p\n", &x);
    // int* p;
    // p=&x;
    // printf("p address is:%p\n",&p);
    // printf("p value is:%p\n",p);
    // *p=*p+1;
    // printf("p value is:%d\n",*p);
    // printf("x value is%d\n",x);
    
    char str[] = "hhhh";
    printf("%s\n",str);
   str[0] = 'j';
    printf("%s\n", str);
char* str1;
strcpy(str1, "hello world");


    return 0;
}