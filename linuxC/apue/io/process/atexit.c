#include <stdlib.h>
#include <stdio.h>
static void f1(void ){
    puts("f1() is working1");
}
static void f2(void ){
    puts("f2() is working1");
}
static void f3(void ){
    puts("f3() is working1");
}
int main(){
    puts("Begin");
    atexit(f1);
    atexit(f2);
    atexit(f3);
    puts("End");
    exit(0);

}