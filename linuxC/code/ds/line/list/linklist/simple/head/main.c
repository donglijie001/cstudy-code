#include <stdio.h>
#include <stdlib.h>
#include "list.h"
int main(){
    list * l;
    l =list_create();
    datatype arr[]= {12,9,23,2,34,6,45};
    if (l==NULL) {
        exit(1);
    }
    #if 0
    for (int i=0; i< sizeof(arr)/sizeof(*arr); i++) {
        if (list_insert_at(l, 0,&arr[i]) !=0) {
            exit(1);
        }
    }
    #endif
    for (int i=0; i< sizeof(arr)/sizeof(*arr); i++) {
        if (list_order_insert(l, &arr[i]) !=0) {
            exit(1);
        }
    }
    list_display(l);
    datatype value;
    int err = list_delete_at(l, 2, &value);
    if (err) {
        exit(1);
    }
    list_display(l);
    printf("delete:%d\n", value);

    #if 0
    datatype value =2;
    list_delete(l,  &value);
    list_display(l);
    #endif

    list_destory(l);

}