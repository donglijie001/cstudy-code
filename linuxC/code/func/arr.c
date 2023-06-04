#include <stdio.h>
#include <stdlib.h>
void print_arr(int *p, int n){

    int i;
    printf("%s:%d\n",__FUNCTION__,sizeof(p));
    
    for( i=0; i< n; i++){
        printf("%d ",*(p + i));
    }
    printf("\n");
}
void func(int * p, int n){
    // 将数组逆序
    int i =0, m = (n-1)/2,j, tmp;
    for(;i <=m;i++){
        j = n-1 -i;
        tmp = p[i];
        p[i] = p[j];
        p[j] = tmp;
    }


}
int main(){
    int a[] ={1,3,5,7,9};
    printf("%s:%d\n",__FUNCTION__,sizeof(a));
    print_arr(a, sizeof(a)/sizeof(*a));
    func(a, sizeof(a)/sizeof(*a));
    print_arr(a, sizeof(a)/sizeof(*a));
    exit(0);
}