#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#include "proto.h"
int main(){
    key_t key=ftok(KEYPATH, KEYPROJ);
    if (key<0) {
        perror("ftok()");
        exit(1);
    }
     // 发送方，没有必要创建消息队列，因为接收方已经创建了
    int msgid=msgget(key, 0);

    if (msgid<0) {
        perror("msgget()");
        exit(1);
    }

    struct msg_st sbuf;
    sbuf.mtype=1;
    strcpy(sbuf.name,"Alan");
    sbuf.math =rand()%100;
    sbuf.chinese =rand()%100;
    if(msgsnd(msgid, &sbuf, sizeof(sbuf)-sizeof(long),0)<0){
        perror("msgsnd()");
        exit(1);
    }
    puts("ok");
    printf("size is%ld\n", sizeof(sbuf));
    exit(0);
}