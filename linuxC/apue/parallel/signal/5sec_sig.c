#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
// 设置编译器不能对其进行优化，保证其内存可见性。
// 如果不加这个关键字的话，使用编译器对这段代码进行优化的话，就会陷入死循环
static volatile int loop =1;
static void alarm_handler(int s){
    loop=0;
}
int main(){
    
    int64_t count =0;
    alarm(5);
    signal(SIGALRM, alarm_handler);
    while (loop) {
        count++;
    }
    printf("%lld\n", count);
    exit(0);
    //下面这版代码，alarm会终止进程，异常终止根本就不会打印count的值
    // 所以使用上面这种，使用signal函数。
    // int64_t count =0;
    // alarm(5);
    // while (1) {
    //     count++;
    // }
    // printf("%lld\n", count);
    // exit(0);

}