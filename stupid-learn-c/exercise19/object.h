#include <stddef.h>
#ifndef _object_h
// 这里相当于是定义了一个空宏，如果没有定义_object_h这个宏，就执行下面这段逻辑
#define _object_h 
typedef enum{
    NORTH, SOUTH,EAST, WEST
}Direction;
typedef struct{
    char * description;
    // 下面全是函数指针，并且使用的是void 指针，就是无类型指针，可以指向任意类型的数据，但是不能解读数据，即不能通过无类型指针进行取数
    int (*init)(void  *self); 
    void (*describe)(void *selef);
    void (*destory)(void *selef);
    void *(*move)(void *self, Direction direction);
    int (*attack)(void *self, int damage);
} Object;
int Object_init(void *selef);
void Object_destory(void *self);
void Object_describe(void *selef);
void *Object_move(void *selef, Direction direction);
int Object_attack(void  *selef, int damage);
// 这里的object实际上是一个struct，并且不是struct指针，而且当作参数传递到函数里，
void *Object_new(size_t size, Object proto, char * descripion);
// 下面定义了一个宏，T##Proto 语法表示“将Proto连接到T的末尾”，所以如果你写下 NEW(Room, "Hello.") ，就会在这里变成 RoomProto 。
#define NEW(T,N) Object_new(sizeof(T), T##Proto,N)
// 这个宏是一种为对象系统设计的“语法糖”，将 obj->proto.blah 简写为 obj->_(blah)
#define _(N) proto.N
#endif
