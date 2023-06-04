#include <stdio.h>
#include <stdlib.h>
#define  M 3
#define  N 4
void print_arr(int *p, int n){
    printf("%s sizeof(p) = %d\n",__FUNCTION__, sizeof(p));
    int j;
    for (j=0; j<n; j++) {
            printf("%d ", p[j]);
    }
    printf("\n");
}
void print_arr1(int (*p)[N],int m, int n){
    //void print_arr1(int p[][N],int m, int n){ 这种方式也可以

    int i,j;
    printf("%s sizeof(p) = %d\n",__FUNCTION__, sizeof(p));

    for (i=0; i<m; i++) {
        for (j =0; j<n; j++) {
            printf("%4d  ", *(*(p +i) +j));
        }
        printf("\n");
    }
}
float average_score(int * p, int n){
    float sum =0.0;
    for (int i=0; i<n; i ++) {
        sum += p[i];
    }
    return sum/n;
}
int main(){
    int i,j;
    // 把下面这个数组当作是M个学生的N个学科的成绩
    int a[M][N] = {1,2,3,4,5,6,7,8,9,10,11,12};
    printf("average_score is %f \n", average_score(*a, M*N));

    #if 0
    printf("%s sizeof(a) = %d\n",__FUNCTION__, sizeof(a));
    print_arr(&a[0][0], M*N);
    print_arr1(a, M, N);
    #endif

    #if 0
    print_arr(*a, M*N);
    print_arr(*(a+0), M*N);
    print_arr(a[0], M*N);
    #endif

    /*
    
    printf("a=>%p\n", a);
    printf("a[0]=>%p\n", *a);
    printf("*a +1=>%p\n", *a +1);
    printf("a[0]+1=>%p\n", a[0]+1);
    printf("*a=>%p\n", *a);
    printf("a[0][0] =>%p\n", &a[0][0]);
    printf("a+1 => %p \n", a+1);
    printf("*(a+1) => %p\n", *(a+1));*/

    exit(0);
}
