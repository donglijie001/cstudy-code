#ifndef LLIST_H__
#define LLIST_H__
#define LLIST_FORWARD 1
#define LLIST_BACKWARD 2

typedef int  llist_cmp(const void *,  const void *);
typedef void  llist_op1 (const void *);

struct llist_node_st{
    struct llist_node_st *prev;
    struct llist_node_st *next;
    // char data[1]； 视频上讲由于指针偏移，会占用4个字节，这个还不太清楚，等后面再好好看看吧。
    char data[0];
};
typedef  struct llist_head{
    int size;
    struct llist_node_st head;
    int (*insert)(struct llist_head * ,const void *, int);
    void * (*find)(struct llist_head * ,const void *, llist_cmp *);
    int(*del)(struct llist_head * ,const void *, llist_cmp *);
    int(*fetch)(struct llist_head * ,const void *, llist_cmp *, void *);
    void (*travel)(struct llist_head *, llist_op1 *);
} LLIST;
//typedef void (*llist_op)(const void *);

// 这是自定义了一个函数，上面那个才是函数指针



LLIST *llist_create(int initsize);





void llist_travel(LLIST *, void (*llist_op)(const void *));

void llist_destory(LLIST *);


#endif