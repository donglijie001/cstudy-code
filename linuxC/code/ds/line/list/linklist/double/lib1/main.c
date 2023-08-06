#include <stdio.h>
#include <stdlib.h>
#include "llist.h"
#define NAMESIZE 32
struct score_st{
    int id;
    char name[NAMESIZE];
    int math;
    int chinese;
};
int main(){
    LLIST *handler;
    handler = llist_create(sizeof(struct score_st));
    struct score_st tmp;
    for(int i=0;i<7;i++){
        tmp.id =i;
        snprintf(tmp.name, NAMESIZE, "std%d", i);
        tmp.math = rand()%100;
        tmp.chinese = rand()%100;
        llist_insert(handler, &tmp, LLIST_FORWARD);
    }
    
    llist_travel(handler);
    llist_destory(handler);
    exit(0);
}