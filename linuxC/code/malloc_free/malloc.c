#include <stdio.h>
#include <stdlib.h>

int main(){
    int *p =NULL;
    p = malloc(sizeof(int));
    if (p==NULL) {
        printf("malloc() error!\n");
    }
    *p=10;
    printf("%p-->%d\n",p, *p);
    free(p);
    // 这就变成了野指针，释放了，就立即把指针指向置为NULL
    p= NULL;
    *p = 123;
    printf("%p-->%d\n",p, *p);
    exit(0);
}