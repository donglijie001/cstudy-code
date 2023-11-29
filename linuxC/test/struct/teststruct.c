#include <stdio.h>
#include <stdlib.h>
struct node_st{char* str;};
struct node_st * node_st_arr[10];

/**
 * 这段代码是我写的用来测试struct的,我在init函数里创建了一个局部变量struct me1,
 然后我在print函数里面去访问，
 一旦 init 函数运行结束后，me1 存储的空间就会被释放掉，
 此时在程序中访问 node_st_arr[1]->str 就会访问非法内存，导致 core dump
 * 
 */
void init(){
    struct node_st *me;
    char * str="aaa";
    me = malloc(sizeof(*me));
    me->str = str;
    node_st_arr[0]= me;
    struct node_st me1;
    me1.str="hhh";
    node_st_arr[1] = &me1;
}
void print(){
    if (node_st_arr[0]!=NULL &&node_st_arr[0]->str!=NULL) {
        printf("node_st->str[0] is not NULL:%s:\n", node_st_arr[0]->str);
    }else {printf("node_st->str[0] is NULL:\n");}
    if (node_st_arr[1]!=NULL &&node_st_arr[1]->str!=NULL) {
        printf("node_st->str[1] is not NULL:%s:\n", node_st_arr[1]->str);
    }else {printf("node_st->str[1] is NULL:\n");}
}
int main(){
    init();
    print();
    exit(0);
}