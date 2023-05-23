#include <stdio.h>
#include <stdlib.h>
#define M 2
#define N 3
int main(void){
    int a[M][N] = {{1,2,3},{4,5,6}};
    int i,j;
    for(i =0;i<M;i++){
        for (j=0; j<N; j++) {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }

}