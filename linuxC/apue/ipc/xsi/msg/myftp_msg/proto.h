// 约定双方的对话格式
#ifndef PROTO_H__
#define PROTO_H__
#define KEYPATH "/etc/services"
#define KEYPROJ 'a'  
#define PATHMAX 1024
#define DATAMAX 1024
enum msg_type {
    MSG_PATH =1,
    MSG_DATA,
    MSG_EOT
};
typedef struct msg_path_st{
    long mtype; // must be MSG_PATH
    char path[PATHMAX]; // ASCII 自带尾0的串
}msg_path_t;
typedef struct msg_data_st{
    long mtype;// must be MSG_DATA
    char path[DATAMAX]; 
    int datalen;
}msg_data_t;
typedef struct msg_eot_st{
    long mtype;// must be MSG_EOT
}msg_eot_t;
/**
 * c端向s端请求获取文件，传递路径名，然后s端给c端返回内容，但是它返回的消息可能是data，
 也有可能是表示文件结束，所以才有了一个字段mtype ，来表示消息类型，但是为了解决c端区分接收到的消息类型，
这里添加了一个共用体msg_s2c_un,在msg_s2c_un中添加了一个字段mtype。无论来的消息是哪种类型，最开始的字段就是mtype。
所以直接根据msg_s2c_un中的mtype字段来看是哪种类型。
 * 
 */
union msg_s2c_un{
    long mtype; 
    msg_data_t datamsg;
    msg_eot_t eotmsg;
};
#endif