#include <stdio.h>
int compare(int a,int b){
    printf("sum is:%d \n",a + b);
}
int main(){
    int (*compare_cb) (int a, int b)= compare;
    compare(1,2);
    compare_cb(1,2);
}