#include <stdio.h>
#include <stdlib.h>
struct node_st{char* str;};
struct node_st * node_st_arr[10];
/**
 * 这段程序是为了测试通过malloc 分配的内存，创建一个struct，然后让其中的str指向一个字符串常量，
然后在另外一个函数里，访问这个字符串常量，是可以访问成功的，"aaa"是一个字符串常量
，存储在程序的静态常量区域，而不是函数内存栈或堆中。因此，不管函数执行结束与否，"aaa"所在的内存空间都不会被回收。
所以我虽然在init 函数里创建了这个字符串常量，仍然可以在print函数里访问。
注意：字符串常量的内存空间在程序一开始就分配好了，它是不可修改的。
如果在初始化之后，试图对该字符串进行修改操作，将会产生未定义的行为，可能造成程序错误。

这个case，输入的实际上是字符串常量，我想试一下，不使用字符串常量，不太行，
因为如果使用char * ,就需要使用malloc分配内存，这个时候就在堆上了，就没有验证的必要了。
 * 
 */
void init(){
    struct node_st *me;
    char * str="aaa";
    me = malloc(sizeof(*me));
    me->str = str;
    node_st_arr[0]=me;
    printf("str:%p,me->str%p\n", &str, &(me->str));
}
void print(){
    printf("node_st_arr[0]!=NULL %d\n", node_st_arr[0]!=NULL);
    if (node_st_arr[0]!=NULL) {
        printf("node_st_arr[0]->str!=NULL %d\n", node_st_arr[0]->str!=NULL);
    }
    if (node_st_arr[0]!=NULL &&node_st_arr[0]->str!=NULL) {
        printf("node_st->str[0] is not NULL:%s:%p\n", node_st_arr[0]->str,node_st_arr[0]->str);
    }else {printf("node_st->str[0] is NULL:\n");}
}
int main(){
    init();
    print();
    exit(0);
}