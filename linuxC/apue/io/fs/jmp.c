#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
static jmp_buf save;
static void d(void){
    printf("%s():Begin.\n", __FUNCTION__);
    printf("%s():Jump now\n",__FUNCTION__);
    // 跳转到跳转点save，并设置返回值6
    longjmp(save,6);
    printf("%s():End.\n", __FUNCTION__);
}
static void c(void){
    printf("%s():Begin.\n", __FUNCTION__);
    printf("%s():Call d().\n", __FUNCTION__);
    d();
    printf("%s():d() returned.\n", __FUNCTION__);
    printf("%s():End.\n", __FUNCTION__);
}
static void b(void){
    printf("%s():Begin.\n", __FUNCTION__);
    printf("%s():Call c().\n", __FUNCTION__);
    c();
    printf("%s():c() returned.\n", __FUNCTION__);
    printf("%s():End.\n", __FUNCTION__);
}
static void a(void){
    int ret;
    
    printf("%s():Begin.\n", __FUNCTION__);
    ret =setjmp(save);
    if (ret ==0) {
        // 返回值为0，说明是设置挑
        printf("%s():Call b().\n", __FUNCTION__);
        b();
        printf("%s():b() returned.\n", __FUNCTION__);
    }else {
        // 跳转回来
        printf("%s():Jumped back here with code:%d\n",__FUNCTION__, ret );
    }
    
    printf("%s():End.\n", __FUNCTION__);
}
int main(){
    printf("%s():Begin.\n", __FUNCTION__);
    printf("%s():Call a().\n", __FUNCTION__);
    a();
    printf("%s():a() returned.\n", __FUNCTION__);
    printf("%s():End.\n", __FUNCTION__);
}