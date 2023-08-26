#include <stdio.h>
#include <stdlib.h>
#include "sqstack.h"
sqlstack * st_create(void){
    sqlstack * st;
    st = malloc(sizeof(*st));
    if (st == NULL) {
        return NULL;
    }

    st->top =-1;
    return st;
}
int st_isempty(sqlstack * st){
    // top 值为-1，就表示栈为空，这个时候跟1比较，就会返回1，c语言里1就表示为true。
    return (st ->top == -1);

}
int st_push(sqlstack * st, datatype * data){
    if (st->top  == (MAXSIZE -1)) {
        return -1;
    }
    st->data[++st->top]= *data;
    return 0;
}
int st_pop(sqlstack * st, datatype * data){
    if (st_isempty(st)) {
        return -1;
    }
    *data = st->data[st->top--];
    return 0;
}
int st_top(sqlstack * st, datatype * data){
    // 栈顶元素不出栈
    if (st_isempty(st)) {
        return -1;
    }
    *data = st->data[st->top];
    return 0;
}

void st_travel(sqlstack * st){
    if (st_isempty(st)) {
        //为空，不进行遍历
        return;
    }
    for (int i=0; i<= st->top; i ++) {
        printf("%d ", st->data[i]);
    }
    printf("\n");

}
void st_destory(sqlstack * st){
    free(st);
}
