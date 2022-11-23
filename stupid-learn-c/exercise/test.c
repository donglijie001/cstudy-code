#include <stdio.h>
int main(){
    int* p;
    int i;

    p = &i;
    *p = 13;
    printf("%d,address:%p, address:%p, address:%p", i,p, &i, &p);
}