#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "llist.h"
#include <string.h>
struct llist_node_st{
    struct llist_node_st *prev;
    struct llist_node_st *next;
    // char data[1]； 视频上讲由于指针偏移，会占用4个字节，这个还不太清楚，等后面再好好看看吧。
    char data[0];
};
struct llist_head_st{
    int size;
    struct llist_node_st head;
    
};
LLIST * llist_create(int initsize){
    struct llist_head_st  * new ;
    new = malloc(sizeof(*new));
    if (new == NULL) {
        return NULL;
    }
    new ->size = initsize;
    new->head.prev = &(new->head);
    new->head.next = &(new->head);
    return new;
}
int  llist_insert(LLIST * p,const void * data, int mode){
    // 需要创建一个llist_node_st，并且其中的data要进行赋值
    struct llist_node_st  *newnode;
    // 申请内存有下面两种方式
    //newnode = malloc(sizeof(struct llist_node_st));
    // 申请内存的时候，要加上即将存入数据的size的值，
    struct llist_head_st *ptr = p;
    newnode = malloc(sizeof(*newnode) + ptr->size);
    if(newnode == NULL){
        return -1;
    }
    // 给data节点申请内存 这一步可以省略
    //newnode->data = malloc(ptr->size);
    // 下面这个判断也可以省略了。
    // if (newnode->data == NULL) { 
    //     return -2;
    // }
    // newnode->data 进行赋值，这里不能直接赋值，需要使用内存拷贝函数
    memcpy(newnode->data, data,ptr->size);

    if (mode == LLIST_FORWARD) {
        //头部插入
        newnode -> prev = &ptr->head;
        newnode ->next = ptr->head.next;
    }else if(mode ==LLIST_BACKWARD) {
        // 尾部插入
        newnode->next = &ptr->head;
        newnode->prev = ptr->head.prev;
    }else {// 错误的插入模式
        // 这个时候应该把申请的内存给释放掉
        free(newnode->data);
        free(newnode);
        return -3;
    }
        newnode->prev->next = newnode;
        newnode->next->prev = newnode;
    // 插入成功后，返回0
    return 0;


}
void llist_travel(LLIST * p, void (*llist_op)(const void *)){
    struct llist_node_st *cur;
    struct llist_head_st *ptr = p;
    for (cur = ptr->head.next; cur!=&ptr->head; cur = cur->next) {
        llist_op(cur->data);
    }

}
void llist_travel1(LLIST * p, llist_op1 * op){
    struct llist_node_st *cur;
    struct llist_head_st *ptr = p;

    for (cur = ptr->head.next; cur!=&ptr->head; cur = cur->next) {
        op(cur->data);
    }

}
void llist_destory(LLIST * p){
    struct llist_head_st *ptr = p;

    struct llist_node_st * cur, * next;
    for (cur = ptr->head.next; cur!= &ptr->head; cur =cur->next) {
        next = cur->next;
        free(cur);
    }
    free(ptr);
}
static struct llist_node_st * find_(LLIST  * p,const void * key, llist_cmp * cmp){
    struct llist_node_st * cur;
    struct llist_head_st *ptr = p;

    for (cur = ptr->head.next; cur!= &ptr->head; cur = cur->next) {
        if (cmp(key,cur->data)==0) {
            //这里假设了数据不会重复
            break;
        }
    }
    // 当找不到数据的时候，就返回头节点，头节点的data就是NULL
    return cur;
    
}
void * llist_find(LLIST  * p,const void * key, llist_cmp * cmp){

    // struct llist_node_st * res= find_(ptr, key, cmp);
    // if (res != NULL) {
    //     return res->data;
    // }
    // return NULL;
    struct llist_head_st *ptr = p;
    struct llist_node_st *node = find_(ptr, key, cmp);
    if (node == &ptr->head) {
        return NULL;
    }
    return node->data;
}
int  llist_delete(LLIST * p, const void * key, llist_cmp * cmp){
    struct llist_node_st *node;
    struct llist_head_st *ptr = p;

    node = find_(ptr, key, cmp);
    if (node == &ptr->head) {
        // 没有找到
        return -1;
    }
    node->prev->next = node ->next;
    node->next->prev = node ->prev;
    //释放内存
    //free(node->data);
    free(node);
    return 0;

}
int  llist_fetch(LLIST *p, const void * key, llist_cmp * cmp, void * data){
    struct llist_node_st *node;
    struct llist_head_st *ptr = p;

    node = find_(ptr, key, cmp);
    if(node == &ptr->head){
        return -1;
    }
    node->prev->next = node ->next;
    node->next->prev = node ->prev;
    if (node !=NULL) {
        memcpy(data, node->data, ptr->size);
    }
    //free(node->data);
    free(node);
    return 0;
}