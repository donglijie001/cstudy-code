#include <stdlib.h>
#include <stdio.h>
#include "proto.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
int main(){
    key_t key=ftok(KEYPATH, KEYPROJ);
    if (key<0) {
        perror("ftok()");
        exit(1);
    }
    // 创建管道，设置权限
    int msgid=msgget(key, IPC_CREAT|0600);
    if (msgid<0) {
        perror("msgget()");
        exit(1);
    }

    struct msg_st rbuf;
    while (1) {
            //减去long 的大小，是因为msgrcv定义的参数里接收数据的结构体包含了,long类型的msgtype
        if(msgrcv(msgid,&rbuf, sizeof(rbuf)-sizeof(long),0,0)<0){
            perror("msgrcv()");
            exit(1);
        }
        printf("NAME=%s\n",rbuf.name);
        printf("MATH=%d\n",rbuf.math);
        printf("CHINESE=%d\n",rbuf.chinese);

    }
    msgctl(msgid, IPC_RMID, NULL);

    exit(0);
}