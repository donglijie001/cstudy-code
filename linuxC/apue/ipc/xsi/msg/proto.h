// 约定双方的对话格式
#ifndef PROTO_H__
#define PROTO_H__
#define KEYPATH "/etc/services"
#define KEYPROJ 'g'  //ascii码会转成一个整型数。
#define NAMESIZE 1024
struct msg_st{
    long mtype;
    char name[NAMESIZE];
    int math;
    int chinese;
};
#endif