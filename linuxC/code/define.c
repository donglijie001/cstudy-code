#include <stdio.h>
#include <stdlib.h>
//#define ADD 2+3
#define MAX(a,b) a>b ? a:b
int main(){
   // printf("%d\n", ADD * ADD);
    int i =5, j=3;
    printf("%d\n",  MAX(i, j));
    exit(0);
}