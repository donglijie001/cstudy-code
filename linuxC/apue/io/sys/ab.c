#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
int main(){
    putchar('a');
    //往标准输出写入内容
    write(1, "b", 1);
    putchar('a');
    //往标准输出写入内容
    write(1, "b", 1);
    putchar('a');
    //往标准输出写入内容
    write(1, "b", 1);
    exit(0);
}