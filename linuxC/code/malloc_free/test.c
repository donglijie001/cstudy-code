#include <stdio.h>
#include <stdlib.h>
void func(int *p, int n){
    p = malloc(n);
    if(p == NULL){
        exit(1);
    }
    return;
}
int main(){

    int num =100;
    int *p = NULL;
    func(p,num);
    free(p);
    exit(0);
 }
