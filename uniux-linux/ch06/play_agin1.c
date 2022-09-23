#include <stdio.h>
#include <sys/termios.h>
#include <termios.h>
#define QUESTION "Do you want another transaction"
/**
 1、对用户显示提示问题
 2、接受输入
 3、如果是'y'，返回0，
 4、如果是'n'，返回1
 存在的问题，1、用户必须按回车键，play_again0 才能接受到数据。
           2、当用户按回车键时，程序接收整行的数据并对其进行处理。
 */
int get_response(char *);
void tty_mode(int how){
    static struct termios original_mode;
    if (how==0) {
        tcgetattr(0 , &original_mode);
    }else {
        tcsetattr(0, TCSANOW, &original_mode);
    }
}
void set_crmode(){
    struct termios ttystate;
    tcgetattr(0, &ttystate);
    ttystate.c_cflag &=~ICANON;
    ttystate.c_cc[VMIN] = 1;
    tcsetattr(0, TCSANOW, &ttystate);
}
int main(){
    int response;
    tty_mode(0);
    set_crmode();
    response = get_response(QUESTION);
    tty_mode(1);
    return response;
}
int get_response(char * question){
    printf("%s(y/n)", question);
    int input;
    while (1) {
        switch (input=getchar()) {
            case 'y':
            case 'Y': return 0;
            case 'n':
            case 'N':
            case EOF: return 1;
            default:
                printf("\ncannot understand %c,", input);
                printf("Please type y or nos \n");
        }
    }
}