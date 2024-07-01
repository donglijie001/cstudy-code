// 约定双方的对话格式
#include <stdint.h>
#ifndef PROTO_H__
#define PROTO_H__
#define RCVPORT "1989"
/*
512是 udp推荐的长度，
减去的第一个8是udp报头的长度，第二个8是math 和chinese这两个变量所占的长度
*/ 
#define NAMEMAX 512 - 8 -8  
// 这里使用柔性数组，用来动态的改变发送的消息的长度
struct msg_st{
    uint32_t math;
    uint32_t chinese;
    uint8_t name[1]; // name[0] 
}__attribute__((packed));//告诉编译器不进行对齐
#endif