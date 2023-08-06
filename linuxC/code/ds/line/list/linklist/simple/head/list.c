#include <stdio.h>
#include <stdlib.h>

#include "list.h"

list *list_create(){
    list * me;
    me = malloc(sizeof(*me));
    if (me == NULL) {
        return NULL;
    }
    me->next = NULL;
    return me;
}
int list_insert_at(list * me, int i, datatype * data){
    int j =0;
    list * node =me;
    list *newnode;
    if (i< 0) {
        return -1;
    }
    while (j< i && node!= NULL) {
        node = node->next;
        j++;
    }
    if (node != NULL) {
        newnode = malloc(sizeof(*newnode));
        if (newnode ==NULL) {
            return -2;
        }
        newnode->data = *data;
        newnode->next =NULL;
        newnode->next = node ->next;
        node->next=newnode;
        return 0;
    
    }else {
        // 说明插入位置不合法，返回-2
        return  -3;
    }
}
int list_order_insert(list *me, datatype * data){
    // 有序插入，
    list *p = me, *q;
    while (p->next!=NULL&&p-> next->data < * data) {
        p=p->next;
    }
    q = malloc(sizeof(*q));
    q->data = *data;
    q->next = p->next;
    p->next =q;
    return 0;
}
int list_delete_at(list *me,int i, datatype *data){
    int j=0;
    list *p = me, *q;
    *data=-1;
    if (i<0) {
        
        return -1;
    }
    while (j<i && p) {
        p=p->next;
        j++;
    }
    if (p) {
        q= p->next;
        p->next = q->next;
        *data = q->data;
        free(q);
        return 0;
    }else {
        return -2;
    }
}
int list_delete(list * me, datatype *data){
    list * p = me, *q;
    while (p->next && p->next->data !=*data ) {
        p= p->next;
    }
    if (p->next==NULL) {
        return -1;
    }else {
        q= p->next;
        p->next = q->next;
        free(q);
        q->next=NULL;
        return 0;
    }
    
}
void list_display(list * me){
    
    if (list_isempty(me)==0) {
        return;
    }
    list * node = me->next;
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
    return;
}
int list_isempty(list * me){
    if (me->next == NULL) {
        return 0;
    }
    return 1;
}
void list_destory(list * me){
    list *node, *next;
    // 这个也可以用while 循环代替
    for(node =me->next;node!=NULL; node = next){
        next = node->next;
        free(node);
    }
    free(me);
    return;
}