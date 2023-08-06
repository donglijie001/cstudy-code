#include <stdio.h>
#include <stdlib.h>
#include "nohead.h"
int list_insert(struct node_st **list, struct score_st *data){
    struct node_st * new;
    new = malloc(sizeof(*new));
    if(new ==NULL){
        return -1;
    }
    new ->data = *data;
    new->next = *list;
    *list = new;
    return 0;
}
void list_show(struct node_st *list){
    struct node_st * cur;
    for(cur = list; cur!=NULL; cur=cur->next){
        printf("id:%d, name:%s chinest:%d,math: %d \n", cur->data.id,
        cur->data.name, cur->data.chinese,cur->data.math);
    }
}
int list_delete(struct node_st **list){
    if (*list == NULL) {
        return -1;
    }
    struct node_st *cur;
    cur = *list;
    *list = (*list)->next;
    free(cur);
    return 0;
}
// int list_find(struct node_st *list, int id){
//     if (list == NULL) {
//         return -1;
//     }
//     struct node_st * cur;
//     for(cur = list; cur!=NULL; cur=cur->next){
//         if (cur->data.id == id) {
//             printf("id:%d, name:%s chinest:%d,math: %d \n", cur->data.id,
//         cur->data.name, cur->data.chinese,cur->data.math);
//             return 0;
//         }
//     }
//     return -2;
// }
struct score_st* list_find(struct node_st *list, int id){
    if (list == NULL) {
        return NULL;
    }
    struct node_st * cur;
    for(cur = list; cur!=NULL; cur=cur->next){
        if (cur->data.id == id) {
            
            return &(cur->data);
        }
    }
    return NULL;
}
void list_destory(struct node_st * list){
    if (list == NULL) {
        return;
    }
    struct node_st *cur;
    for (cur = list; cur != NULL;cur = list ) {
        list = cur->next;
        free(cur);
    }
}