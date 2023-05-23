#include <stdio.h>
#include <stdlib.h>

int main(){
    int i = 1;
    int *p;
    p =&i;
    char* ch;
    printf("%d\n", sizeof(p));
    printf("%d\n", sizeof(ch));

#if 0
    printf("i = %d\n", i);
    printf("&i = %p\n", &i);
    printf("p = %p\n", p);
    printf("&p = %p\n", &p);
    printf("*p = %d\n", *p);
#endif

    exit(0);
}