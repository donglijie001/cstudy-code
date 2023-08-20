#ifndef LLIST_H__
#define LLIST_H__
#define LLIST_FORWARD 1
#define LLIST_BACKWARD 2

struct llist_node_st{
    struct llist_node_st *prev;
    struct llist_node_st *next;
    // char data[1]； 视频上讲由于指针偏移，会占用4个字节，这个还不太清楚，等后面再好好看看吧。
    char data[0];
};
typedef  struct{
    int size;
    struct llist_node_st head;

} LLIST;
//typedef void (*llist_op)(const void *);

// 这是自定义了一个函数，上面那个才是函数指针
typedef void  llist_op1 (const void *);

typedef int  llist_cmp(const void *,  const void *);

LLIST *llist_create(int initsize);

int  llist_insert(LLIST *,const void * data, int mode);
void * llist_find(LLIST *, const void * key, llist_cmp *);
int  llist_delete(LLIST *, const void * key, llist_cmp *);
int  llist_fetch(LLIST *, const void * key, llist_cmp *, void * data);
void llist_travel(LLIST *, void (*llist_op)(const void *));
void llist_travel1(LLIST *, llist_op1 *);

void llist_destory(LLIST *);


#endif