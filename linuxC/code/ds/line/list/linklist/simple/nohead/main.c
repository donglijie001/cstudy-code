#include <stdio.h>
#include <stdlib.h>
#include "nohead.h"

int main(){
    struct node_st *list =NULL;
    struct score_st tmp;
    int ret;
    for (int i=0;i<7;i++){
        tmp.id = i;
        // 这个函数第一次用到
        snprintf(tmp.name, NAMESIZE, "stu%d", i);
        tmp.math= rand()%100;
        tmp.chinese =rand()%100;
        ret = list_insert(&list, &tmp);
        if(ret !=0){
            exit(1);
        }

    }
    list_show(list);
    printf("\n\n");
    // list_delete(&list);
    // list_show(list);
    struct score_st *ptr;
    ptr = list_find(list, 3);
    if (ptr ==NULL) {
        printf("Can not find!\n");
    }else {
    printf("id:%d, name:%s chinest:%d,math: %d \n", ptr->id,
        ptr->name, ptr->chinese,ptr->math);
    }
    list_destory(list);
    exit(0);
}
