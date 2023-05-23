#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(void){
    char str[] = "hello\0abc";
    printf("%u\n", strlen(str));
    printf("%u\n", sizeof(str));
    exit(0);
}