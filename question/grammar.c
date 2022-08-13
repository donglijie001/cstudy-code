#include <stdio.h>

// sprintf 用法
void sprintf_usage(){
    /*
        格式化输出到字符串，这个函数，很不安全，因为，输出到to数组的字符串，有可能回超过to 数组的长度限制
        ,并且使用这个函数，不能声明一个指针，需要声明一个字符串数组。否则会报错
    */
    char to[80];
    // X 大写输出的是大写十六进制字母，x小写输出的是十六进制的小写字母
    sprintf(to, "%02X", 12);
    printf("%s\n",to);

}
void printf_usage(){
    // 输出字符串，%02x 是按照16进制输出，如果不足两位用0来填充，如果写成%2x，不足两位就会用空格来填充
    printf("%02x\n", 18);
}
void snprintf_usage(){
    /*
        sprintf 存在问题，因为输出到字符串里可能会超过字符串的长度限制，因此使用snprintf，这个函数，可以限制输出到to到字符串长度，
        限制的长度包含了末尾的空白字符，在c语言里，声明一个字符串，使用char数组格式声明的话，数组长度是包含字符串末尾的空白字符的。
    */
    char to[4];
    snprintf(to, 4, "%02X:", 18);
    printf("%s\n",to);

}
int main(){
    //printf_usage();
    //sprintf_usage();
    snprintf_usage();

    
    
}