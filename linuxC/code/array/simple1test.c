#include <stdio.h>
#include <stdlib.h>
static void fibonacci(void){
    int fib[10] ={1,1};
    for (int i=2; i<10; i ++) {
        fib[i] = fib[i -1] + fib[i-2];
    }
    for (int i=0; i<10; i++) {
        printf("%d  ", fib[i]);
    }
    printf("\n");
    return;
}
#define N 10
void bubble_sort(){
    int a[N] = {12,8,45,30,98,67,2,7,68,11};
    int tmp;
    for (int i=0; i< N; i ++) {
        printf("%d ", a[i]);
    }
    printf("\n");
    for (int i=0;i<N-1; i++) {
        for (int j=0;j <N-1-i; j ++) {
            if (a[j] > a[j+1]) {
             tmp = a[j];
             a[j] = a[j+1];
             a[j + 1] = tmp;
            }
        }
    }
    for (int i=0; i< N; i ++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}
void select_sort(){
    int a[N] = {12,8,45,30,98,67,2,7,68,11};
    int tmp,k;
    for (int i=0; i< N; i ++) {
        printf("%d ", a[i]);
    }
    printf("\n");
    for(int i =0 ; i < N - 1; i++){ // i小于N或者i小于N-1 都没有关系
        k = i;
        for ( int j= i +1; j<N; j++) {
            if (a[j] < a[k]) {
                k = j;
            }
        }
        if (k!= i) {
           tmp = a[i];
           a[i] = a[k];
           a[k] = tmp;
        }

    }
    for (int i=0; i< N; i ++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}
void base_convert(){
    int num, base;
    int n[128],i=0;
    printf("Please enter the convert number:");
    scanf("%d", &num);
    printf("Please enter the convert base:");
    scanf("%d", &base);
    do {
     n[i]= num %base;
     num = num /base;
     i ++;
    }while (num !=0);
    for (i --; i>=0; i--) {
        if (n[i]>=10) {
        printf("%c ", n[i] -10 + 'A');
        }else {
        printf("%d ", n[i]);
        }
    }
    printf("\n");

}
static void primer(void){
    char primer[1001] = {0};
    for (int i =2; i<1001;i++) {
        if (primer[i] ==0) {
            for (int j = i*2; j<1001;  j +=i) {
                primer[j] =-1;
            }
        }
    }
    printf("0-1000 primer is:");
    for (int i=2; i<1001; i++) {
        if (primer[i]==0) {
            printf("%d ",i);
        }
    }
    printf("\n");
}
int main(void){
    //fibonacci();
    //bubble_sort();
    //select_sort();
    //base_convert();
    primer();
    exit(0);
}