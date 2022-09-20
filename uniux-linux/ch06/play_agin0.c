#include <stdio.h>
#include <termios.h>
#define QUESTION "Do you want another transaction"
/*
 1、对用户显示提示问题
 2、接受输入
 3、如果是'y'，返回0，
 4、如果是'n'，返回1
 存在的问题，1、用户必须按回车键，play_again0 才能接受到数据。
            2、当用户按回车键时，程序接收整行的数据并对其进行处理。
*/
int get_response(char *);
int main(){
    int response;
    response = get_response(QUESTION);
    return response;
}
int get_response(char * question){
    printf("%s(y/n)", question);
    while (1) {
       int res = getchar();
       printf("%c\n",res); //我把getchar给提出来了，用来输出打印结果
        switch (res) {
            case 'y':
            case 'Y': return 0;
            case 'n':
            case 'N':
            case EOF: return 1;
            
        }
    }
}