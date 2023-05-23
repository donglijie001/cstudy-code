#include <stdio.h>
#include <stdlib.h>
#define M 2
#define N 3
static void conver_arr(void){
    int i,j;
    int a[M][N]={1,2,3,4,5,6},b[N][M];
    for (i =0; i<M; i++) {
        for (j =0; j<N; j++) {
            printf("%d ", a[i][j]);
            b[j][i]= a[i][j];
        }
        printf("\n");
    }
    for (i =0; i<N; i++) {
        for (j =0; j<M; j++) {
            printf("%d ", b[i][j]);
        }
        printf("\n");
    }
}
static void max(void){
    int a[M][N] = {43,4,23,89,9,7};
    int i,j;
    int max =a[0][0], row=0, col =0;
    for(i =0;i<M;i++){
        for (j=0; j<N; j++) {
            if(max < a[i][j]){
                max = a[i][j];
                row = i;
                col = j;
            }
        }
    }
    printf("max value is:%d, row is %d, col is:%d \n", max,row, col);
}
int main(){
    //conver_arr();
    max();
    exit(0);
}