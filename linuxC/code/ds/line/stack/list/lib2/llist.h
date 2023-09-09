#ifndef LLIST_H__
#define LLIST_H__
#define LLIST_FORWARD 1
#define LLIST_BACKWARD 2
typedef  void LLIST; // 这里使用void，让用户不感知内部使用的数据结构
typedef int  llist_cmp(const void *,  const void *);
typedef void  llist_op1 (const void *);
LLIST *llist_create(int initsize);
int  llist_insert(LLIST *,const void * data, int mode);
void * llist_find(LLIST *, const void * key, llist_cmp *);
int  llist_delete(LLIST *, const void * key, llist_cmp *);
int  llist_fetch(LLIST *, const void * key, llist_cmp *, void * data);
void llist_travel(LLIST *, void (*llist_op)(const void *));
void llist_travel1(LLIST *, llist_op1 *);


void llist_destory(LLIST *);


#endif