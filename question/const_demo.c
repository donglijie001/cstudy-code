#include <stdio.h>
int main(){
    // 声明一个字符串
    char * s = "ss";
    printf("%s\n",s);

    //定义一个常量字符串
    const char * ss = "ssss";
    printf("%s\n",ss);
    ss = "ddd";
    printf("%s\n",ss);
    char const *sss = "dd";
    printf("%s\n",sss);

    sss = "ddd";
    printf("%s\n",sss);
    char * const ssss = "hhh";
    printf("%s\n",ssss);
    //ssss = "jjj";
    printf("%s\n",ssss);



}