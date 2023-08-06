#include <stdio.h>
#include <stdlib.h>
#include "llist.h"
LLIST * llist_create(int initsize){
    LLIST * new ;
    new = malloc(sizeof(*new));
    if (new == NULL) {
        return NULL;
    }
    new ->size = initsize;
    new->head.data = NULL;
    new->head.prev = &(new->head);
    new->head.next = &(new->head);
    return new;
}
int  llist_insert(LLIST * ptr,const void * data, int mode){

}
void llist_travel(LLIST * ptr){

}
void llist_destory(LLIST * ptr){
    struct llist_node_st * cur, * next;
    for (cur = ptr->head.next; cur!= &ptr->head; cur =cur->next) {
        next = cur->next;
        free(cur->data);
        free(cur);
    }
    free(ptr);

}