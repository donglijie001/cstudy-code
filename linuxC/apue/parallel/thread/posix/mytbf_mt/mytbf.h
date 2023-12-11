#ifndef MYTBF_H__
#define MYTBF_H__
#define MYTBF_MAX 1024

typedef void mytbf_t;
// void * 类型的指针，可以赋值给任何类型的指针,这种是一种类似面向对象的方式
mytbf_t * mytbf_init(int cps, int burst);
int mytbf_fetchtoken(mytbf_t *, int);
int mytbf_returntoken(mytbf_t *, int);
int mytbf_destory(mytbf_t *);
#endif