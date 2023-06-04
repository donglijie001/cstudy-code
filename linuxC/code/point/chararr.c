#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(){
    char *str = "helloll";
    printf("%u %u\n", sizeof(str), strlen(str));
 //   strcpy(str,"world");  str指向了一个串常量，所以在拷贝的时候会出错。
    str = "worldll";
    puts(str);
    #if 0
    char str[] = "hello";
    // 下面这行代码有问题，数组名是一个常量是不能在除初始化的情况下进行赋值
   // str = "world"; 
   // sizeof 包含尾0， strlen不包含尾0，遇到尾0就终止，即使尾0在字符中间
    printf("%u %u\n", sizeof(str), strlen(str));
   strcpy(str,"world");
   puts(str);
   #endif
    exit(0);
}