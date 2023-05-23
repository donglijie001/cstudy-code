# 资料

视频链接：https://www.bilibili.com/video/BV18p4y167Md

同步代码到服务器：

```
rsync -av /Users/donglijie/Desktop/selfLearning/cstudy-code donglijie@192.100.219.110:/home/donglijie
```



# 1 学习方法和基本概念简单介绍

学习建议：

1、概念的正确性

2、动手能力

3、阅读优秀的程序段

4、大量练习，面试题

c课程讲解思路

​	1、基本概念

​	2、数据类型，运算符和表达式

​	3、输入输出专题

​    4、流程控制

​	5、数组

​	6、指针

​    7、函数

​    8、构造类型

​	9、动态内存管理

​	10、调试工具（gdb,make）

​	11、常用库函数

## 1.2 gcc与vim的使用

hello world 程序，c语言main函数定义有很多种，在该课程里面，如果main函数不需要传参数，就定义成 int main(void), 如果需要传参数就定义成int main(int arc, char ** argv);

![image-20230514202911185](note.assets/image-20230514202911185.png)

hello.c到可执行文件

编译器：gcc

c源文件->预处理->编译->汇编->链接

预处理： gcc -E hello.c > hello.i

编译：gcc -S hello.i 或gcc -S hello.i -o hello.s

汇编：gcc -c hello.s -o hello.o

链接： gcc hello.o -o hello

编辑器：

vim 熟悉vim常用的脚本

我不太想用vim。后面再说吧。

## 1.3 基本概念

写代码的时候把gcc报的warnging都给解决掉，除非你能确认这个warnging对程序无影响。

gcc 编译的时候， -Wall 选项可以打印出所有的警告

1、以hello world 程序为例

- 头文件包含的重要性
- 以函数为单位进行编程
- 声明部分+ 定义部分

 **echo $?** 在shell脚本中输出上一条命令的返回值。

- return 0;

- 添加注释

  #if  0 也可以添加注释

2、算法：解决问题的办法（流程图、NS图、有限状态机FSM）

3、程序：用某种语言实现算法

4、进程：

​	防止写越界，防止内存泄漏，谁打开谁关闭，谁申请谁释放。

# 2 数据类型，运算符和表达式

## 2.1 数据类型（基本数据类型）

如下图

![image-20230516223545217](note.assets/image-20230516223545217.png)

![image-20230516224118817](note.assets/image-20230516224118817.png)

1）所占字节数

2）存储和区别

​	整型数在计算机中是以补码的形式进行存储。

​	float， 对于 32 位的浮点数，最高的 1 位是符号位 s ，接着的 8 位是指数 E ，剩下的 23 位为有效数字 M。[参考链接](https://www.jb51.net/article/244252.htm)

​	增加实数存储的详细过程，[参考链接](https://zhuanlan.zhihu.com/p/152338612)

​	c 语言char 型变量是有符号还是无符号是未定义的。

3）不同类型的数据间进行转换（隐式转换或显式转换-->强制类型转换）

​	隐士转换： 比如double 和 int 相加，会先把int 转成double然后进行操作。	

4）特殊性

​	（1）布尔型 bool

​	（2）float 类型

​			它是无法和一个准确的数值进行相等比较的，比如下图中的代码和0进行比较应该是和0相减，看它的精度，在某个范围内认为是0.

​		![image-20230517090104294](note.assets/image-20230517090104294.png)

​		（3） char型是否有符号是未定义

​		（4） 不同状态下的零值 0，'0'，"0",'\0'

​		（5）数据类型与后续代码中所使用的输入输出要相匹配（防止自相矛盾）。

## 2.2 常量与变量

常量：在程序执行过程中值不会发生变化的量。

​	分类：整型常量、实型常量、字符常量、字符串常量、标识常量

​			整型常量：1，2，3

​			实型常量：3.14

​			字符常量：由单引号引起来的单个字符或转义字符，如'a'、'\n'、'\t'、'\015'、'\x7f'、'\018'(这是一个错误的字符)。

​			<img src="note.assets/image-20230517135243642.png" alt="image-20230517135243642" style="zoom:50%;" />

​			字符串常量：由双引号引起来的一个或多个字符组成的序列。如：""(这个叫空串),"a"，"XYZ"，"abc\n\021\018"



变量：用来保存一些特定内存，并且在程序执行过程中值随时会发生变化的量。

标识常量： #define，处理在程序的预处理阶段，占编译时间，参数一改，全改，缺点：不检查语法，只是单纯的宏名和宏体的替换。

```
#define 宏名 宏体 # 在预处理阶段，宏名会被宏体替换
```

![image-20230518083019988](note.assets/image-20230518083019988.png)

```
#include <stdio.h>
#include <stdlib.h>
#define ADD 2+3
int main(){
    printf("%d\n", ADD * ADD);
    exit(0);
}

编译： make define
运行：./define 
输出结果： 11
查看预处理结果：gcc -E define.c 
```

![image-20230518133343547](note.assets/image-20230518133343547.png)

可以看到在预处理阶段，ADD 被完整替换为了2+3 ，所以程序运行的输出结果是11.

然后我们使用带参数的宏

![image-20230518083350630](note.assets/image-20230518083350630.png)

考虑到运算符的优先级，应该给每个变量都加上括号

![image-20230518083554085](note.assets/image-20230518083554085.png)

![image-20230518083705780](note.assets/image-20230518083705780.png)

由于上面是完整替换，所有i的值会被计算两次，这是因为宏是完整替换。为了解决这个问题，可以使用函数来代替宏，也可以在宏里面使用变量接收传入的参数

![image-20230518084505431](note.assets/image-20230518084505431.png)

**变量的定义与声明**

![image-20230518090349894](note.assets/image-20230518090349894.png)

变量： 用来保存一些特定内容，并且在程序执行过程中值随时会发生变化的量。

定义：[存储类型] 数据类型 标识符 = 值

​				TYPE	NAME = VALUE

​	标识符：由字符，数字，下划线组成且不能以数字开头的一个标识序列。

​	数据类型：基本数据类型 + 构造类型

​	值：注意匹配。

​	存储类型：auto static register extern（说明型）

​			auto： 默认，自动分配空间，自动回收空间，它不会对变量进行初始化，如下代码 auto.c

```
#include <stdio.h>
#include <stdlib.h>
int main(){
    auto int i;
    int j;
    printf("i = %d\n", i);
    printf("j = %d\n", j);
    exit(0);
}
```

运行结果：![image-20230518214910898](note.assets/image-20230518214910898.png)

​			regiter：（建议型，编译器可以不采用）寄存器类型，只能定义局部变量，不能定义全局变量，大小有限制，只能定义32位大小的数据类型，如double就不可以，寄存器没有地址，所以一个寄存器类型的变量无法打印出地址查看或使用。

​			static： 静态型，自动初始化为0值或者空值，并且这种变量的值有继承性，也可以用来修饰变量或者函数(修饰全局变量和函数，就只能在当前文件中使用，不能在其他文件中使用)。

​			extern：说明型，意味着不能改变被说明的变量的值或类型,该变量在其他文件里面声明，没有必要在当前文件里面为它分配空间。通常用来表示，该变量是多个文件共享的。。

```
#include <stdio.h>
#include <stdlib.h>
void func(void){
    int x=0;
    x = x+1;
    printf("%p ->%d\n", &x,x);
}
int main(){
    func();
    func();
    func();
    exit(0);
}
```

运行结果：

![image-20230518215546081](note.assets/image-20230518215546081.png)

如果把x声明为static。

```
#include <stdio.h>
#include <stdlib.h>
void func(void){
   static int x=0;
    x = x+1;
    printf("%p ->%d\n", &x,x);
}
int main(){
    func();
    func();
    func();
    exit(0);
}
```

![image-20230518215637335](note.assets/image-20230518215637335.png)

```
static说明符对于全局变量和局部变量有不同的含义。

（1）用于局部变量（位于块作用域内部）。

static用于函数内部声明的局部变量时，表示该变量的值会在函数每次执行后得到保留，下次执行时不会进行初始化，就类似于一个只用于函数内部的全局变量。由于不必每次执行函数时，都对该变量进行初始化，这样可以提高函数的执行速度，详见《函数》一章。

（2）用于全局变量（位于块作用域外部）。

static用于函数外部声明的全局变量时，表示该变量只用于当前文件，其他源码文件不可以引用该变量，即该变量不会被链接（link）。

static修饰的变量，初始化时，值不能等于变量，必须是常量。
```

​			extern：说明型，意味着不能改变被说明的变量的值或类型。

变量的生命周期和作用范围

​	1） 全局变量和局部变量

​		作用范围是从定义位置开始，一直到作用域结束，如果同时有全局变量和局部变量，则以局部变量为准。

**全局变量的冲突**

​		依次创建如下文件：main.c    project.c project.h，内容如下

```
#include <stdio.h>
#include <stdlib.h>
#include "project.h"
int i=10;
int main(){
    printf("[%s]:i = %d \n",__FUNCTION__, i);
    funcTest();
    exit(0);
}
```

```
#include <stdio.h>
#include <stdlib.h>
#include "project.h"
int i =100;
void funcTest(void){
    printf("[%s]:i = %d \n",__FUNCTION__, i);
    exit(0);
}
```

```
#ifndef PROJECT_H__
#define PROJECT_H__
void funcTest(void);
#endif
```

编译结果：

![image-20230519085102035](note.assets/image-20230519085102035.png)

因为在两个文件里，都定义了一个全局变量i，所以导致了冲突。

这个时候就可以使用static关键字修饰，这样表示这个变量只能在当前文件中使用。

2）局部变量之间的区别	

![image-20230519133518800](note.assets/image-20230519133518800.png)

## 2.3 运算符和表达式

取余：% 要求两边都是正数。

sizeof： 是一个运算符，不是关键字。		

位运算：

​	将操作数中第n位置1，其他位不变：num = num |1 <<n

​	将操作数中第n位置0，其他位不变：num = num &~(1 <<n)

​	测试第n位：if（num & 1 <<n）

​	从一个指定宽度的数中取出其中的某几位。

# 3 输入、输出专题

标准IO和文件IO



格式化输入输出函数：scanf，printf

​	int printf(const char * format,...)

![image-20230519211648318](note.assets/image-20230519211648318.png)

printf 加上\n，会刷新缓冲区。

scanf

​	int scanf(const char *format, ...);

​	抑制符： *

```
#include <stdio.h>
#include <stdlib.h>
int main(void){
    int i;
    float f;
    printf("Please enter:\n");
    scanf("%d%f", &i, &f);
    printf("i = %d\n", i);
    printf("f = %f\n", f);
    exit(0);
}
```

<img src="note.assets/image-20230520110424166.png" alt="image-20230520110424166" style="zoom:50%;" />

scanf 输入多个参数的时候，比如上面输入i和f，输入的格式字符串是"%d%f"，所以在输入的时候，可以按空格或者按回车或者按tab用来分割两个数，如果在格式字符串里加上一个逗号，那输入的时候就要按照这个格式，在两个数字之间加上逗号，否则就会有问题。

scanf 的返回值，用来表示输入的元素是否真的匹配。

抑制符 *

对于下面这样一段代码：

我定义了一个int i，然后定义了char ch，预期是我输入一个数字，然后再输入一个字符，然后程序再原样输出。但是运行结果如下，当我输入数字后，按照回车程序就结束了。程序输出的字符是换行。

```
#include <stdio.h>
#include <stdlib.h>
int main(void){
    int i;
    float f;
    char ch;
    scanf("%d", &i);
    scanf("%c", &ch);
    printf("i = %d,ch = %d\n", i, ch);
#if 0
    printf("Please enter:\n");
    scanf("%d#%f", &i, &f);
    printf("i = %d\n", i);
    printf("f = %f\n", f);
#endif

    exit(0);
}
```

![image-20230520113118109](note.assets/image-20230520113118109.png)

可以使用抑制符吞掉一个字符，把那个字符不赋值給ch。对应代码：`scanf("%*c%c", &ch);`



![image-20230520113545691](note.assets/image-20230520113545691.png)

此外，scanf输入字符串(%s)的时候，不能在字符串中间上分割符，比如空格、tab等等，而且使用scanf输入字符串的时候有可能会出现溢出，就是限制输入字符串的长度N，可以输入超过N个字符。

字符输入输出函数：getchar,putchar

字符串输入输出函数：gets，puts

​	gets函数没有对输入的字符串的长度进行校验。可以使用fgets来代替。

# 4 流程控制

画流程图可以使用Dia，[参考链接](https://zhuanlan.zhihu.com/p/366116011)

# 5 数组

## 5.1一维数组

定义：[存储类型] 数据类型 标识符

初始化： 使用static 声明数组，默认初始化为0

元素引用：数组名[下标]

数组名：数组名是表示地址的常量，也是数组的起始位置。

数组越界：完全没有校验

获取数组长度； sizeof(arr)/sizeof(arr[0])，就是数组总的长度除第一个元素的长度。

练习题：

1、fibonacci数列(求前十项)

2、数据排序

3、进制转换（终端输入十进制数，然后再输入要转换的进制）

4、删除法求质数（求1000以内，从2到1000，从2开始，把2，3，4等等一系列的倍数都删除，最后得出来的就是质数）

```
#include <stdio.h>
#include <stdlib.h>
static void fibonacci(void){
    int fib[10] ={1,1};
    for (int i=2; i<10; i ++) {
        fib[i] = fib[i -1] + fib[i-2];
    }
    for (int i=0; i<10; i++) {
        printf("%d  ", fib[i]);
    }
    printf("\n");
    return;
}
#define N 10
void bubble_sort(){
    int a[N] = {12,8,45,30,98,67,2,7,68,11};
    int tmp;
    for (int i=0; i< N; i ++) {
        printf("%d ", a[i]);
    }
    printf("\n");
    for (int i=0;i<N-1; i++) {
        for (int j=0;j <N-1-i; j ++) {
            if (a[j] > a[j+1]) {
             tmp = a[j];
             a[j] = a[j+1];
             a[j + 1] = tmp;
            }
        }
    }
    for (int i=0; i< N; i ++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}
void select_sort(){
    int a[N] = {12,8,45,30,98,67,2,7,68,11};
    int tmp,k;
    for (int i=0; i< N; i ++) {
        printf("%d ", a[i]);
    }
    printf("\n");
    for(int i =0 ; i < N - 1; i++){ // i小于N或者i小于N-1 都没有关系
        k = i;
        for ( int j= i +1; j<N; j++) {
            if (a[j] < a[k]) {
                k = j;
            }
        }
        if (k!= i) {
           tmp = a[i];
           a[i] = a[k];
           a[k] = tmp;
        }

    }
    for (int i=0; i< N; i ++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}
void base_convert(){
    int num, base;
    int n[128],i=0;
    printf("Please enter the convert number:");
    scanf("%d", &num);
    printf("Please enter the convert base:");
    scanf("%d", &base);
    do {
     n[i]= num %base;
     num = num /base;
     i ++;
    }while (num !=0);
    for (i --; i>=0; i--) {
        if (n[i]>=10) {
        printf("%c ", n[i] -10 + 'A');
        }else {
        printf("%d ", n[i]);
        }
    }
    printf("\n");

}
static void primer(void){
    char primer[1001] = {0};
    for (int i =2; i<1001;i++) {
        if (primer[i] ==0) {
            for (int j = i*2; j<1001;  j +=i) {
                primer[j] =-1;
            }
        }
    }
    printf("0-1000 primer is:");
    for (int i=2; i<1001; i++) {
        if (primer[i]==0) {
            printf("%d ",i);
        }
    }
    printf("\n");
}
int main(void){
    //fibonacci();
    //bubble_sort();
    //select_sort();
    //base_convert();
    primer();
    exit(0);
}
```

## 5.2二维数组

定义，初始化：[存储类型] 数据类型 标识符[行下标] [列下标]

​	二维数组定义时只有行号可以省略。

二维数组名是数组的起始值。

练习题：

1、行列互换

2、求最大值及其所在为i饿汉子

3、求各行各列的和

4、矩阵乘积

```
#include <stdio.h>
#include <stdlib.h>
#define M 2
#define N 3
static void conver_arr(void){
    int i,j;
    int a[M][N]={1,2,3,4,5,6},b[N][M];
    for (i =0; i<M; i++) {
        for (j =0; j<N; j++) {
            printf("%d ", a[i][j]);
            b[j][i]= a[i][j];
        }
        printf("\n");
    }
    for (i =0; i<N; i++) {
        for (j =0; j<M; j++) {
            printf("%d ", b[i][j]);
        }
        printf("\n");
    }
}
static void max(void){
    int a[M][N] = {43,4,23,89,9,7};
    int i,j;
    int max =a[0][0], row=0, col =0;
    for(i =0;i<M;i++){
        for (j=0; j<N; j++) {
            if(max < a[i][j]){
                max = a[i][j];
                row = i;
                col = j;
            }
        }
    }
    printf("max value is:%d, row is %d, col is:%d \n", max,row, col);
}
int main(){
    //conver_arr();
    max();
    exit(0);
}
```

二维数组实际上就是一个数组的数组。

比如int a[2] [3];这是一个两行三列的数组。a就是一个行指针。

![image-20230521191258963](note.assets/image-20230521191258963.png)

## 5.3字符数组

初始化，使用字符初始化，或者使用字符串常量初始化。

strlen函数获取字符串长度，遇到尾0（\0），就停止，比如这个字符串"hello\0abc"，输出的实际上就不对。输出的是5，但是实际上是10，sizeof 计算的是字符串在内容中的占用的字节数。

```
char str[] = "hello\0abc";
    printf("%u\n", strlen(str)); // 输出5
    printf("%u\n", sizeof(str)); // 输出10
```

strcpy 拷贝字符串

strncpy 拷贝字符串，同时指定长度。

# 6 指针

1、变量与地址的关系

​	变量实际上就是地址的别名，指针就是地址。

2、指针与指针变量

​	用来保存指针的变量。从下面这张图可以看出，指针变量就是一级一级的嵌套。

![image-20230522090018616](note.assets/image-20230522090018616.png)

​	i 值是1

​	&i（i的地址）0x2000

​	p的值0x2000

​	&p的地址是0x3000

​	*p（获取p指向的值） *(0x2000) ->1

i<=>*p， i和 *p是等价的。

&i<=> p i的地址和p的值是等价的。

​	q：0x3000 （存储的是p的地址）

​	&q： 0x4000

​	*q： *（&p）->p -> &i , q指针的内容是0x3000，0x3000是一个地址， * 就是获取这个地址里面存储的内容，所以就是获取）0x3000里面存储的内容，就是0x2000，也就是i的地址，也是p的值。

​    **q： *( *q) -> *（p）->1 这个就相当于是获取p指向的值。

现在想要获取i就有三种方式：i<=>*p<=> **q

通过i获取值是直接访问，通过p获取i的值是间接访问。

```
#include <stdio.h>
#include <stdlib.h>

int main(){
    int i = 1;
    int *p;
    p =&i;
    printf("i = %d\n", i);
    printf("&i = %p\n", &i);
    printf("p = %p\n", p);
    printf("&p = %p\n", &p);
    printf("*p = %d\n", *p);


    exit(0);
}
运行结果：
i = 1
&i = 0x7ff7bac6c518
p = 0x7ff7bac6c518
&p = 0x7ff7bac6c510
*p = 1
```

不同类型的指针，在同一平台下面所占大小是一样的。比如下面这段代码，在32位的机器上输出的是4，

```
int *p;
    p =&i;
    char* ch;
    printf("%d\n", sizeof(p));
    printf("%d\n", sizeof(ch));
```

3、直接访问和间接访问

4、空指针与野指针	

```
int *p = NULL; // 定义空指针
野指针：当前指针指向的地址是不确定的。
```

5、空类型

6、定义与初始化的书写规则

```
int *p = NULL; // 没有确定指针的指向，就让它先指向NULL
```

7、指针运算

​	&（取地址） *（取值） 关系运算 ++ --

8、指针与数组

​	指针与一维数组

```
#include <stdio.h>
#include <stdlib.h>
int main(){
    int a[3] = {1,2,3};
    int *p = a;
    int i;
    /*
        a[i] = *(a + i) = *(p + i) = p[i]
        &a[i] = a + i = p + i = &p[i]
        获取数组长度可以使用： sizeof(a)/sizeof(a[0]) 或者 sizeof(a)/sizeof(*a)
        p和a 都可以用来访问数组，它俩之间的区别，a是常量，p是变量，也就是a在初始化以后，
        就不能再赋值，但是p是可以赋值
    */
    for (i=0; i< sizeof(a)/sizeof(a[0]);  i ++) {
        //printf("%p ->%d \n",&a[i], a[i]);
       // printf("%p ->%d \n",a + i, a[i]);
         printf("%p ->%d \n",p + i, a[i]);
    }
    printf("\n");
    exit(0);
}
```

​	

​	指针与二维数组

​	指针与字符数组

9、const与指针

10、指针数组和数组指针

11、多级指针

