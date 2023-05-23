#include <stdio.h>
#include <stdlib.h>
void func1(void){
   static int x=0;
    x = x+1;
    printf("%p ->%d\n", &x,x);
}
int main(){
    func1();
    func1();
    func1();
    exit(0);
}