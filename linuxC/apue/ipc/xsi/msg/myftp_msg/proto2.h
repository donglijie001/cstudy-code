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
typedef struct msg_s2c_st{
    long mtype;
    int datalen;
    /*
    datalen >0 data包， 
            =0 eot
    */ 
    char path[DATAMAX]; 
    
}msg_data_t;


#endif