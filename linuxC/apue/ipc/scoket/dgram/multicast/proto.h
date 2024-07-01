// 约定双方的对话格式
#include <stdint.h>
#ifndef PROTO_H__
#define PROTO_H__
#define MTGROUP "224.2.2.2"
#define RCVPORT "1989"
#define NAMESIZE 11
struct msg_st{
// 这个程序有些问题，就是name 的长度是固定的。
    uint8_t name[NAMESIZE];
    uint32_t math;
    uint32_t chinese;
}__attribute__((packed));//告诉编译器不进行对齐
#endif