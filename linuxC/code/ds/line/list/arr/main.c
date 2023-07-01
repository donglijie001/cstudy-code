#include <stdio.h>
#include <stdlib.h>
#include "sqlist.h"
int main(){
    sqlist *list = NULL, *list1 = NULL;
    datatype arr[] = {12,23,34,45,56};
    datatype arr1[] = {89,90,78,67,56,45};
    int i;
    //list = sqlist_create();
    // 这里使用的是二级指针，二级指针变量存储的是地址。
    //因此把list的地址传递过去，用一个二级指针去接收
    sqlist_create1(&list);
    if (list == NULL) {
        fprintf(stderr, "sqlist_create() failed");
        exit(1);
    }
    list1 = sqlist_create();
    if (list1 == NULL) {
        fprintf(stderr, "sqlist_create() failed");
        exit(1);
    }
    // 求数组长度也可以用sizeof(arr)/sizeof(arr[0])
    for (i =0; i<sizeof(arr)/sizeof(*arr); i++) {
       int  err = sqlist_insert(list, 0, &arr[i]);
       if (err !=0) {
            if (err==-1) {
                    fprintf(stderr, "The arr is full");
            }else if (err ==-2) {
                    fprintf(stderr, "The pos you want to insert is wrong.\n");
            }else {
                    fprintf(stderr, "Error.\n");
            }
            exit(1);
       }
    }
    sqlist_display(list);
    for (i =0; i<sizeof(arr1)/sizeof(*arr1); i++) {
       int  err = sqlist_insert(list1, 0, &arr1[i]);
       if (err !=0) {
            if (err==-1) {
                    fprintf(stderr, "The arr is full");
            }else if (err ==-2) {
                    fprintf(stderr, "The pos you want to insert is wrong.\n");
            }else {
                    fprintf(stderr, "Error.\n");
            }
            exit(1);
       }
    }
    sqlist_display(list1);
    sqlist_union(list, list1);
    sqlist_display(list);
#if 0
    sqlist_delete(list, 1);
    printf("after delete：");
    sqlist_display(list);
#endif
    sqlist_destory(list);
    sqlist_destory(list1);

    exit(0);
}