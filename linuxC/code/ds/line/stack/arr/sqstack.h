#ifndef SQSTACK_H__
#define SQSTACK_H__
#define MAXSIZE 5
typedef int datatype;
typedef struct node_st{
    datatype data[MAXSIZE];
    // top 表示栈顶元素。
    int top;
} sqlstack;
sqlstack * st_create(void);
int st_isempty(sqlstack *);
int st_push(sqlstack *, datatype *);
int st_pop(sqlstack *, datatype *);
int st_top(sqlstack *, datatype *);

void st_travel(sqlstack *);
void st_destory(sqlstack *);
#endif