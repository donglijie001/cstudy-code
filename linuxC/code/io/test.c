#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define WEIGHT 3.0e-23
#define KQ 950
static void water(void){
    // 水分子质量为3.0*e-23，一夸脱水950克，从终端输入夸脱数，求有多少个水分子
    float num;
    float sum;
    printf("Please input for num:");
    scanf("%f",&num);
    sum = num * KQ / WEIGHT;
    printf("total is %e\n",sum);
}
static void area(void){
    // 输入三角形的三边，求面积
    float a,b,c;
    float s,area;
    printf("Please input:");
    scanf("%f%f%f", &a,&b,&c);
    s = 1.0 / 2 *(a + b + c);
    area = sqrt( s * (s-a) * (s -b) * (s - c));
    printf("area = %f\n", area);
}
int main(){
    //water();
    area();
    exit(0);
}