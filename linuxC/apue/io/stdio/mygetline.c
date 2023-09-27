#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
/**
 * 实现的类似getline函数的功能，一开始linebuf为null，然后申请内存，随着内容越来越多，然后在realloc扩展内存
 */
 int add_char_to_linebuf(char ** linebuf, uint32_t * linesize, int ch){
    // 把字符给加到linebuf里，如果满了的话，就调用realloc函数再获取内存。
    // 先构建一个字符串tmp，然后调用字符串拼接函数，把字符串tmp给拼接到linebuf里。
    char tmp[2]={ch};
    // 拼接之前先看linebuf是不是已经满了
    int len= strlen(*linebuf);
    // strlen 返回字符串长度不包含尾0，因此，需要加1
    if (*linesize == (len+1)) {
        // 这个时候说明分配的空间已满，需要扩大内存。
        // 这里直接扩大二倍
        *linesize = 2*(*linesize); 
        *linebuf= realloc(*linebuf, (*linesize) *sizeof(char));
        if (*linebuf == NULL) {
            perror("realloc");
            exit(1);
        }
    }
    strcat(*linebuf, tmp);
    return 0;
}
 int add_char_to_linebuf1(char * linebuf, uint32_t * linesize, int ch){
    // 把字符给加到linebuf里，如果满了的话，就调用realloc函数再获取内存。
    // 先构建一个字符串tmp，然后调用字符串拼接函数，把字符串tmp给拼接到linebuf里。
    char tmp[2]={ch};
    // 拼接之前先看linebuf是不是已经满了
    int len= strlen(linebuf);
    // strlen 返回字符串长度不包含尾0，因此，需要加1
    if (*linesize == (len+1)) {
        // 这个时候说明分配的空间已满，需要扩大内存。
        // 这里直接扩大二倍
        *linesize = 2*(*linesize); 
        linebuf= realloc(linebuf, (*linesize) *sizeof(char));
        if (linebuf == NULL) {
            perror("realloc");
            exit(1);
        }
    }
    strcat(linebuf, tmp);
    return 0;
}
int get_line(char **linebuf, uint32_t * linesize,FILE * stream){
    if (*linesize==0) {
        *linesize=2;
    }
    if (*linebuf== NULL) {
        // 函数第一次进入，这个时候，就需要分配内存，
        *linebuf = malloc((*linesize) *sizeof(char));
        
    }
    if (*linebuf== NULL) {
        // 分配内存不成功，直接返回
        return -2;
    }
    // 内存分配成功，开始读取文件内容，要先判断stream是否为null，为null直接返回
    if (stream==NULL) {
        return -3;
    }
    // 文件流不为空，开始读取文件，这里使用fgetc。
    int ch;
    // 读之前把linebuf全部置为空
    memset(*linebuf, '\0', *linesize);
    while (1) {
        ch = fgetc(stream);
        if (ch==EOF ) {
            // 读到的字符等于EOF，说明到了文件结尾了，这个时候，就该停止了
            break;
        }
        if (ch=='\n') {
            // 等于换行符，说明读到了一行的结尾,这个时候需要把读取到的换行符给添加到linebuf中
            add_char_to_linebuf(linebuf, linesize, ch);
            //add_char_to_linebuf1(*linebuf, linesize, ch);

            break;
        }
        add_char_to_linebuf(linebuf, linesize, ch);
        //add_char_to_linebuf1(*linebuf, linesize, ch);

    }
    // 返回一行读取的字符数
    int len=strlen(*linebuf);
    if (ch==EOF && len ==0) {
        return -1;
    }
    return len;
}

int main(int argc,char ** argv){
    if (argc <2) {
        fprintf(stderr, "invalid argument\n");
        exit(1);
    }
    //以只读模式打开文件
    FILE * fp = fopen(argv[1], "r");
    if (fp==NULL) {
        // 打印失败原因
        perror("fopen()");
        exit(1);
    }

    char* linebuf=NULL;
    uint32_t linesize=0;
    int count=0;
    while (1) {
        if ((count=get_line(&linebuf, &linesize, fp))<0) {
            // 返回结果小于0，说明结束了。
            break;
        }
        printf("content:%s\n", linebuf);
        printf("linesize:%d\n",linesize);
        printf("readcount:%d\n", count);

    }
    // 关闭指针
    fclose(fp);
    free(linebuf);
    printf("%d\n",sizeof(char));

    
#if 0
    char * str =malloc(6 *sizeof(char));
    printf("sizeof(str):%d\n", sizeof(*str));
    if (*str =='\0') {
        printf("str only have '\\0'\n");
    }
    printf("%s\n", str);
    printf("%d\n", *str);
    char string[2]={'a'};
    strcat(str,string);
    char string1[2]={'b'};

    strcat(str,string1);
    printf("after add sizeof(str):%d\n", sizeof(*str));
    printf("first character%c\n", *(str+1));

    printf("strlen(str):%d\n", strlen(str));
    printf("%s\n", str);
    printf("sizeof(char):%d", sizeof(char));
    int* i = malloc(sizeof(int));

    printf("i%d\n", *i);
#endif


    exit(0);
}