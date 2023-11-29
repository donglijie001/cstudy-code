#include <stdio.h>
#include <stdlib.h>
struct node_st{char* str; char * str1;};
struct node_st * node_st_arr[10];
/**
 * 这段程序是为了测试通过malloc 分配的内存，创建一个struct，然后让其中的str指向一个字符串数组,str1 指向malloc分配的字符串数组，
然后在另外一个函数里，访问struct中的str1和str2，
比较幸运，这段代码并没有出现coredump，
但是运行结果str变成了乱码，因为str是一个局部变量，而str1是通过malloc分配的，所以没有问题。
 * 
 */
void init(){
    struct node_st *me;
    char str[11];
    char* str1 = (char*) malloc(10 * sizeof(char));
     for (int i = 0; i < 10; i++) {
        str[i] = 'a' ;  // 生成随机小写字母
        str1[i] = 'a' ;  // 生成随机小写字母

    }
    str[10] = '\0'; // 添加字符串结尾标识符
    me = malloc(sizeof(*me));
    me->str = str;
    me->str1= str1;
    node_st_arr[0]=me;
    printf("%s\n", str);
    printf("str:%p,me->str%p\n", &str, &(me->str));
    printf("node_st->str[0] is not NULL:%s:%p\n", node_st_arr[0]->str,node_st_arr[0]->str);
    printf("node_st->str1[0] is not NULL:%s:%p\n", node_st_arr[0]->str1,node_st_arr[0]->str1);


}
void print(){
    printf("node_st_arr[0]!=NULL %d\n", node_st_arr[0]!=NULL);
    if (node_st_arr[0]!=NULL) {
        printf("node_st_arr[0]->str!=NULL %d\n", node_st_arr[0]->str!=NULL);
    }
    fflush(NULL);
    printf("\n");
    if (node_st_arr[0]!=NULL &&node_st_arr[0]->str!=NULL) {
        printf("node_st->str[0] is not NULL:%s:%p\n", node_st_arr[0]->str,node_st_arr[0]->str);
    printf("node_st->str1[0] is not NULL:%s:%p\n", node_st_arr[0]->str1,node_st_arr[0]->str1);

    }else {printf("node_st->str[0] is NULL:\n");}
}
int main(){
    
    init();
    print();
    exit(0);
}