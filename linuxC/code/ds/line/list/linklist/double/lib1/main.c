#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "llist.h"
#define NAMESIZE 32
struct score_st{
    int id;
    char name[NAMESIZE];
    int math;
    int chinese;
};
static void print_s(const void *record){
    const struct score_st *r = record; 
    printf("%d %s %d %d\n", r->id, r->name, r->math, r->chinese);
}
// static 关键字表示该方法只能在当前文件里使用
static int id_cmp(const void * key, const void * record){
    const int * k =key;
    const struct score_st * r= record;
    // 为0 就说明找到了
    return  (*k- r->id);
}
static int name_cmp(const void * key, const void * record){
    const char * k =key;
    const struct score_st * r= record;
    // 为0 就说明找到了
    return  strcmp(k, r->name);
}
int main(){
    LLIST *handler;
    handler = llist_create(sizeof(struct score_st));
    if (handler == NULL) {
        exit(1);
    }
    struct score_st tmp;
    for(int i=0;i<7;i++){
        tmp.id =i;
        snprintf(tmp.name, NAMESIZE, "std%d", i);
        tmp.math = rand()%100;
        tmp.chinese = rand()%100;
        int  ret = llist_insert(handler, &tmp, LLIST_FORWARD);
        if (ret) {
            // 不为0，就表示创建失败
            exit(1);
        }
    }
    
    llist_travel(handler, print_s);
    //llist_travel1(handler, print_s);

    printf("\n\n");
    
    int id=rand()%10;
    //这是按照id进行删除
    //int ret = llist_delete(handler, &id, id_cmp);
    // if (ret) {
    //     printf("llist_deleter id:%d failed!\n", id);
    // }
    // 按照性能
    char * del_name ="std6";
    int ret = llist_delete(handler, del_name, name_cmp);
    if (ret) {
        printf("llist_deleter name:%s failed!\n", del_name);
    }
    llist_travel(handler, print_s);
#if 0
    struct score_st *data;
    int id=rand()%10;
    data = llist_find(handler,&id, id_cmp);
    if (data == NULL) {
        printf("Can not find id:%d\n", id);
    } else {
        print_s(data);
    }

    llist_destory(handler);
#endif
    exit(0);
}