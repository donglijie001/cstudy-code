安装中文输入法：https://forum.cool-pi.com/topic/470/ubuntu22-04%E5%AE%89%E8%A3%85fcitx5%E4%B8%AD%E6%96%87%E8%BE%93%E5%85%A5%E6%B3%95

## 2、linux系统安装和基本使用

**strace 追踪工具**

![image-20240920134333236](./ysyxnote.assets/image-20240920134333236.png)

![image-20240920134624433](./ysyxnote.assets/image-20240920134624433.png)

例2中，第3条命令修改了PATH的值

```
strace 的常用选项包括 -o（将输出重定向到文件）、-f（监视被跟踪进程所创建的所有子进程）、-e（指定要跟踪的系统调用或信号）
```

```
 pgrep pateran  查找符合条件的进程
 lsof -p 进程号查看打开的文件。
```

### 环境配置

看参考文档，建议安装桌面版，因此，我安装了我的旧的mac 电脑，安装过程很简单，使用的镜像是22.04，

里面有一条，禁止ubuntu自动更新，同时也建议关闭自动更新的提示，我使用的是：`sudo apt-get remove update-notifier update-manager` [参考链接](https://askubuntu.com/questions/446395/how-to-turn-off-software-updater-xubuntu)，然后是设置静态ip，我手动设置，ip地址是172.16.251.128

```
sudo apt install openssh-server  # 安装ssh server 
```

### Installing Tools

#### Setting APT source file

```
# 资料上有一段是给当前用户加入sudo权限，但是普通用户本身就有，我觉得不用加了。
# 修改软件源
sudo sed -i "s/archive.ubuntu.com/mirrors.tuna.tsinghua.edu.cn/g" /etc/apt/sources.list
# 刷新源
sudo apt-get update 
# 我更新失败了，应该是因为安装Ubuntu时默认源选择了国内镜像, 导致默认的sources.list被修改造成的
# 执行下面这条命令就可以了
sed -i "s/cn.mirrors.tuna/mirrors.tuna/g" /etc/apt/sources.list
sudo apt-get install build-essential    # build-essential packages, include binary utilities, gcc, make, and so on
sudo apt-get install man                # on-line reference manual
sudo apt-get install gcc-doc            # on-line reference manual for gcc
sudo apt-get install gdb                # GNU debugger
sudo apt-get install git                # revision control system
sudo apt-get install libreadline-dev    # a library used later
sudo apt-get install libsdl2-dev        # a library used later

```

**安装中文输入法**

https://blog.csdn.net/windson_f/article/details/124932523

**安装完整版的vim**

```
sudo apt-get remove vim-common
sudo apt-get install vim
```

**关闭升级的自动通知** https://www.11343.com/8094.html

```
sudo bash -c 'echo X-GNOME-Autostart-enabled=false >> /etc/xdg/autostart/update-notifier.desktop'
sudo bash -c 'echo X-GNOME-Autostart-enabled=false >> /etc/xdg/autostart/snap-userd-autostart.desktop'
```

**终端显示路径过长** [参考链接](https://askubuntu.com/questions/145618/how-can-i-shorten-my-command-line-bash-prompt)

![image-20240925004253859](./ysyxnote.assets/image-20240925004253859.png)

```
Remove the @\h, and replace the \w with an uppercase \W
```

![image-20240925004344569](./ysyxnote.assets/image-20240925004344569.png)

**安装和使用tmux**

[ysyx参考链接](https://ysyx.oscc.cc/docs/ics-pa/0.5.html#installing-tmux)

[tmux参考链接1](https://www.cnblogs.com/liuxinxin21d/articles/16651761.html)

[tmux参考链接2](https://www.ruanyifeng.com/blog/2019/10/tmux.html)

```
如果使用tmux的话
需要在tmux.conf文件中加上下面的内容，否则会提示color not enough。
# 设置终端类型为256色
if-shell '[ $(uname -s) = Linux ]' \
    'set -g default-terminal "screen-256color"'
开启鼠标模式：
set -g mouse on

配置完以后，
输入tumx 启动
输入ctrl +b 然后输入快捷键
tmux快捷键说明

#窗格操作

% 左右平分出两个窗格

" 上下平分出两个窗格

x 关闭当前窗格

{ 当前窗格前移

} 当前窗格后移

; 选择上次使用的窗格

o 选择下一个窗格，也可以使用上下左右方向键来选择

space 切换窗格布局，tmux 内置了五种窗格布局，也可以通过 ⌥1 至 ⌥5来切换

z 最大化当前窗格，再次执行可恢复原来大小

q 显示所有窗格的序号，在序号出现期间按下对应的数字，即可跳转至对应的窗格

#窗口操作

c 新建窗口，此时当前窗口会切换至新窗口，不影响原有窗口的状态

p 切换至上一窗口

n 切换至下一窗口

w 窗口列表选择，注意 macOS 下使用 ⌃p 和 ⌃n 进行上下选择

& 关闭当前窗口

, 重命名窗口，可以使用中文，重命名后能在 tmux 状态栏更快速的识别窗口 id

0 切换至 0 号窗口，使用其他数字 id 切换至对应窗口

f 根据窗口名搜索选择窗口，可模糊匹配

#会话操作

$ 重命名当前会话

s 选择会话列表

d detach 当前会话，运行后将会退出 tmux 进程，返回至 shell 主进程
```

下面的部分可以不用看了，都是在centos上操作的。

安装 vmware work fusion 在Mac M3处理器上，然后安装虚拟机，我使用的是arm版的ubuntu22.04.5 镜像https://cdimage.ubuntu.com/jammy/daily-live/current/，但是感觉这个也不是lts版本，先暂时装一下, 虚拟机打开以后，这个时候貌似并没有真正的安装，可以点击里面的程序继续安装，但是我看了ysyx配置环境的资料，要求的cpu架构是x64的，这就很尴尬，在m3的mac上装虚拟机是不行了。[查看系统硬件信息](https://www.cnblogs.com/ggjucheng/archive/2013/01/14/2859613.html)，所以暂时使用我的腾讯云服务器吧，当前腾讯云服务器还是只有root 用户，先加一个普通用户,[参考链接](https://www.digitalocean.com/community/tutorials/how-to-add-and-delete-users-on-a-centos-7-server)

```
useradd donglijie # 创建这个用户是为了和我的mac电脑保持一致，这样就不用输用户名登录，创建用户的时候通用也会创建一个用户组。
passwd donglijie # 修改密码
sudo usermod -aG wheel donglijie # 给donglijie 用户执行权限
```

![image-20240921130649209](./ysyxnote.assets/image-20240921130649209.png)

添加完用户以后，可以看到在wheel用户组下面多了一个用户。

![image-20240921125750544](./ysyxnote.assets/image-20240921125750544.png)

而且通过groups 可以看到用户所属的用户组。

```
[root@VM-8-5-centos donglijie]# groups donglijie
donglijie : donglijie wheel
```

centos安装c语言man手册 [参考链接](https://lanlan2017.github.io/blog/1.9662e+45/)

```
sudo yum install man-pages  
# 不要用下面这个，会把man 手册给变成中文，虽然可以通过export LANG=en_US.UTF-8 来修改回去。

yum install man-pages.noarch ，我的centos 没有装man手册，在man 3 printf的时候提示找不到
```

让vi默认指向vim。[参考链接](https://unix.stackexchange.com/questions/645442/adding-vi-to-vim-mapping-for-all-users-in-centos)

```
alias vi=vim  # 这里我使用了别名
```

linux 命令示例

```

```

## 3、计算机系统的状态机模型

### 3.1 程序是个状态机

c语言程序真的是从main()第一条语句开始执行的吗？

```
int main(){return 0;}
```

```
编译：gcc a.c
使用strace ./a.out, 可以看到输出了很多内容
```

![image-20241014134039145](./ysyxnote.assets/image-20241014134039145.png)

也可以使用gdb去理解这个问题，使用`starti`命令

![image-20241014134151055](./ysyxnote.assets/image-20241014134151055.png)

#### 编译环境和执行环境

[参考链接](https://www.cnblogs.com/XIEjm/p/12870698.html)

c语言入口真的是main函数吗？https://blog.csdn.net/qq_37756660/article/details/133507842

## 4、 从C语言到二进制程序

[参考资料](https://ysyx.oscc.cc/slides/2306/04.html#/%E9%A2%84%E5%A4%84%E7%90%86-%E6%96%87%E6%9C%AC%E7%B2%98%E8%B4%B4)

### 4.1 预处理

预处理=文本粘贴

C程序如何从源代码生成指令序列(二进制可执行文件)：预处理 -> 编译 -> 汇编 -> 链接 -> 执行

```
#include <stdio.h>
#define MSG "Hello \
World!\n"
int main() {
  printf(MSG /* "hi!\n" */);
#ifdef __riscv
  printf("Hello RISC-V!\n");
#endif
  return 0;
}
```

```
上面这样一段代码，执行 gcc -E a.c
下面会输出很多内容，有很多都不是a.c里面的，大部分内容都是吧stdio.h文件里的内容被包含进来了。
```

#### 头文件是符合找到的？

方法：**阅读工具的日志**(查看是否支持`verbose`, `log`等选项)

```
gcc -E a.c --verbose > /dev/null
```

通过man gcc并搜索-I选项可得知头文件搜索的顺序，如下图所示：不过我是通过Directories关键字查找的，不是通过I这个关键字，通过-I 是可以快速搜到的，需要加上短横线。

```
echo '#warning I am wrong!' > stdio.h
gcc -E a.c --verbose
mkdir aaa bbb
gcc -E a.c -Iaaa -Ibbb --verbose > /dev/null
echo '#warning I am wrong, too!' > bbb/stdio.h
echo '#define printf(...)' >> bbb/stdio.h
gcc -E a.c -Iaaa -Ibbb --verbose
```

<img src="./ysyxnote.assets/image-20241016133150373.png" alt="image-20241016133150373" style="zoom:50%;" />

#### 类函数宏

```
#define max(a, b) ((a) > (b) ? (a) : (b))

预处理阶段只进行文本粘贴, 不求值

小心优先级!
好的编程习惯 -> 总是用括号包围参数
小心副作用!
好的编程习惯 -> 一个参数尽量不要展开多次
如何实现?
#define max(a, b) ({ int x = a; int y = b; x > y ? x : y; })
上述代码使用了GNU C Extension, 跨平台移植时需要注意
```

[gnunc extension](https://gcc.gnu.org/onlinedocs/gcc-12.2.0/gcc/C-Extensions.html)

#### 预处理的其他工作

![image-20241016134831878](./ysyxnote.assets/image-20241016134831878.png)

### 4.2. 编译

```
# 安装risvc64 gnu
apt-get install g++-riscv64-linux-gnu
在.bashrc加上下面的
alias rv32gcc="riscv64-linux-gnu-gcc -march=rv32g -mabi=ilp32"
```

编译生成汇编代码。

![image-20241017134204685](./ysyxnote.assets/image-20241017134204685.png)

#### 词法分析

![image-20241017134451759](./ysyxnote.assets/image-20241017134451759.png)

#### 语法分析

![image-20241017134659382](./ysyxnote.assets/image-20241017134659382.png)

#### 语义分析

![image-20241017134806237](./ysyxnote.assets/image-20241017134806237.png)

#### 静态程序分析

![image-20241017134947004](./ysyxnote.assets/image-20241017134947004.png)

#### 中间代码生成

![image-20241017135306421](./ysyxnote.assets/image-20241017135306421.png)

#### 中间代码作为抽象层

<img src="./ysyxnote.assets/image-20241017135702574.png" alt="image-20241017135702574" style="zoom:50%;" />

#### 优化

<img src="./ysyxnote.assets/image-20241017135743054.png" alt="image-20241017135743054" style="zoom:50%;" />

![image-20241017140029086](./ysyxnote.assets/image-20241017140029086.png)

#### 目标代码生成

![image-20241018161413921](./ysyxnote.assets/image-20241018161413921.png)

###  4.3 汇编

![image-20241018161908502](./ysyxnote.assets/image-20241018161908502.png)

objdump查看 二进制目标文件，这里可以指定riscv64的别名，`alias rvobjdump="riscv64-linux-gnu-objdump"`

### 4.4 链接

![image-20241018164429212](./ysyxnote.assets/image-20241018164429212.png)

printf 的代码在哪里这个跟动态链接有关系。暂时先跳过

### 4.5 执行

![image-20241018164620403](./ysyxnote.assets/image-20241018164620403.png)

安装qemu

```
# 通过一些配置工作, RISC-V的可执行文件也可以在本地执行
# apt-get install qemu-user qemu-user-binfmt
# mkdir -p /etc/qemu-binfmt
# ln -s /usr/riscv64-linux-gnu/ /etc/qemu-binfmt/riscv64
```



### 4.6 实现定义行为和ABI

![image-20241027192934927](./ysyxnote.assets/image-20241027192934927.png)

![image-20241027193530606](./ysyxnote.assets/image-20241027193530606.png)

```
根据C语言的运算规则，当一个无符号类型的操作数参与了与符号类型的运算，那么符号类型会被自动转换为无符号类型，且结果也会被视为无符号类型。

因此，对于表达式 6 - 2147483648，2147483648 是一个常量，如果被解释为有符号数，那么会超出32位的表示范围，产生未定义行为。而如果被解释为无符号数，它被视为一个很大的无符号整数，并且会被转换为无符号类型。

在转换为无符号类型之后，表达式的计算过程如下：

- 将2147483648看作一个无符号整数，其补码表示为10000000000000000000000000000000；
- 对6和2147483648都进行常规的整型提升，转成无符号整数；
- 在无符号整数的运算中，减法就是将两个操作数相减，相减的结果也是无符号整数，即：将10000000000000000000000000000000减去6的无符号整数值，结果是2147483642。 

```



## 5、程序的执行和模拟器

### 5.1freestanding运行时环境

#### 编译到freestanding

![image-20241027174430922](./ysyxnote.assets/image-20241027174430922.png)

```
上面先创建一个a.c文件。编译，生成一个.out文件。使用rvobjdump 可以查看二进制文件，rvobjdump这是个别名，在第四堂课已经配置过了。
apt-get install qemu-system # 完全安装qemu
rv32gcc -ffreestanding -nostdlib -Wl,-Ttext=0x80000000 -O2 a.c # 执行编译
qemu-system-riscv32 -nographic -M virt -bios none -kernel a.out # 运行结果如下图。输出A就进行了死循环。
# 这里可以通过输入ctrl +a，然后在按x，就可以从终端中退出qemu。
```

![image-20241028130225130](./ysyxnote.assets/image-20241028130225130.png)

查看二进制文件的反汇编：`rvobjdump -d a.out | vim -`

如下，可以看到编译到fressstanding环境，代码少了很多，更易于学习。

```
donglijie@cloud111:~/ysyxcode/05$ rvobjdump -d a.out

a.out:     file format elf32-littleriscv


Disassembly of section .text:

80000000 <_start>:
80000000:	100007b7          	lui	a5,0x10000
80000004:	04100713          	li	a4,65
80000008:	00e78023          	sb	a4,0(a5) # 10000000 <_PROCEDURE_LINKAGE_TABLE_+0xffffe20>
8000000c:	0000006f          	j	8000000c <_start+0xc>
```

#### 程序如何结束运行

```
C99上面有规定，程序结束，是由实现的环境去决定的。
5.1.2.1 Freestanding environment

2 The effect of program termination in a freestanding environment is
implementation-defined.
```

在qemu-system-riscv32中的virt机器模型中, 往一个特殊的地址写入一个特殊的 “暗号”即可结束QEMU的运行

```
#include <stdint.h>
void _start() {
  volatile uint8_t *p = (uint8_t *)(uintptr_t)0x10000000;
  *p = 'A';
  volatile uint32_t *exit = (uint32_t *)(uintptr_t)0x100000;# 这一行和下面那行注释掉的话，会不断地输出A
  *exit = 0x5555; // magic number
  _start();
}
```

运行结果如下图：

![image-20241028133051073](./ysyxnote.assets/image-20241028133051073.png)

#### 自制一个freestanding运行时环境

![image-20241028133223271](./ysyxnote.assets/image-20241028133223271.png)

[ABI Mnemonic](https://github.com/riscv-non-isa/riscv-elf-psabi-doc/blob/master/riscv-cc.adoc)

####  将程序编译到自制freestanding运行时环境

```
static void ebreak(long arg0, long arg1) {
  asm volatile("addi a0, x0, %0;"
               "addi a1, x0, %1;"
               "ebreak" : : "i"(arg0), "i"(arg1));
}
static void putch(char ch) { ebreak(0, ch); }
static void halt(int code) { ebreak(1, code); while (1); }

void _start() {
  putch('A');
  halt(0);
}
```

```
rv32gcc -ffreestanding -nostdlib -static -Wl,-Ttext=0 -O2 -o prog a.c #编译-Ttext=0 指定程序从哪个地址开始执行。
rvobjdump -M no-aliases -d prog #查看反汇编
```

查看反汇编，可以看到下面只有addi和ebreak指令，还有一条jal指令（这条指令视频说先忽略，这个应该是一个返回操作，但是程序应该执行上一条就结束了。）

```
donglijie@cloud111:~/ysyxcode/05/myfreestanding$ rvobjdump -M no-aliases -d prog

prog:     file format elf32-littleriscv


Disassembly of section .text:

00000000 <_start>:
   0:	00000513          	addi	a0,zero,0
   4:	04100593          	addi	a1,zero,65
   8:	00100073          	ebreak
   c:	00100513          	addi	a0,zero,1
  10:	00000593          	addi	a1,zero,0
  14:	00100073          	ebreak
  18:	0000006f          	jal	zero,18 <_start+0x18>
```

我们需要实现这个运行时环境，才能执行上面的代码。

### 5.2YEMU指令如何执行

#### **回顾: ISA手册定义了一个状态机**

![image-20241028221513295](./ysyxnote.assets/image-20241028221513295.png)

只要用代码把上面的状态机实现出来，就可以用它来执行指令了。

#### **用C代码实现ISA状态机 = 指令集模拟器**

![image-20241028221856425](./ysyxnote.assets/image-20241028221856425.png)

#### **用变量实现寄存器和内存**

![image-20241029131321650](./ysyxnote.assets/image-20241029131321650.png)

#### **用语句实现指令的语义**

![image-20241029131546733](./ysyxnote.assets/image-20241029131546733.png)

![image-20241029131908007](./ysyxnote.assets/image-20241029131908007.png)

```
void inst_cycle() {
  uint32_t inst = *(uint32_t *)&M[PC]; // 取出来pc对应的
  if (((inst & 0x7f) == 0x13) && ((inst >> 12) & 0x7) == 0) { // addi 
  // 上面这个判断，是先取指令的0到6位，判断是不是0x13（0010011），然后再判断第12位到第14位是不是000
    if (((inst >> 7) & 0x1f) != 0) {
    // 上面这个判断7到11位是不是不为0，因为addi操作以后要把结果写到rd里。因为rsicv手册规定0号寄存器永远为0
    // 下面的语义就是rd=rs1+立即数（这里做了一个符号扩展）
      R[(inst >> 7) & 0x1f] = R[(inst >> 15) & 0x1f] +
        (((inst >> 20) & 0x7ff) - ((inst & 0x80000000) ? 4096 : 0));
    }
  } else if (inst == 0x00100073) { // ebreak
    if (R[10] == 0) { putchar(R[11] & 0xff); }
    else if (R[10] == 1) { halt = true; }
    else { printf("Unsupported ebreak command\n"); }
  } else { printf("Unsupported instuction\n"); }
  PC += 4;// 更新寄存器，这里为啥加4我实际上有点疑问，应该是跟*(uint32_t *)&M[PC]这样一个运算有关系。
}
```

#### **初始状态**

![image-20241029221827274](./ysyxnote.assets/image-20241029221827274.png)

这里unspecified是类似implementation-defined

#### YEMU v1.0

```
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
uint32_t R[32], PC;
uint8_t M[64] = {
  0x13, 0x05, 0x00, 0x00, 0x93, 0x05, 0x10, 0x04, 0x73, 0x00, 0x10, 0x00,
  0x13, 0x05, 0x10, 0x00, 0x93, 0x05, 0x00, 0x00, 0x73, 0x00, 0x10, 0x00,
  0x6f, 0x00, 0x00, 0x00,
};
bool halt = false;

void inst_cycle() {
  uint32_t inst = *(uint32_t *)&M[PC]; 
  if (((inst & 0x7f) == 0x13) && ((inst >> 12) & 0x7) == 0) { // addi
    if (((inst >> 7) & 0x1f) != 0) {
      R[(inst >> 7) & 0x1f] = R[(inst >> 15) & 0x1f] +
        (((inst >> 20) & 0x7ff) - ((inst & 0x80000000) ? 4096 : 0));
    }
  } else if (inst == 0x00100073) { // ebreak
    if (R[10] == 0) { putchar(R[11] & 0xff); }
    else if (R[10] == 1) { halt = true; }
    else { printf("Unsupported ebreak command\n"); }
  } else { printf("Unsupported instuction\n"); }
  PC += 4;
}

int main() {
  PC = 0; R[0] = 0; // can be omitted since uninitialized global variables are initialized with 0
  while (!halt) { inst_cycle(); }
  return 0;
}

0x13, 0x05, 0x00, 0x00 对应addi指令 0:	00000513          	addi	a0,zero,0
小端序：就是低位字节存在内存地址的低地址端，
大端序：低位字节存在内存地址的高地址端
数组的0地址是低地址，加下标索引地址增加，所以取M数组中的元素，就相当于是小端序存储。

```

[大端序小端序](https://www.cnblogs.com/still-smile/p/11595775.html)

####  从文件读入程序

![image-20241030132017672](./ysyxnote.assets/image-20241030132017672.png)

### 5.3 编写可读可维护代码

yemu v1.0 实际上也不是那么好，可以继续优化。

#### 防御性编程

![image-20241030133119204](./ysyxnote.assets/image-20241030133119204.png)

#### 改进1: 让断言失败时输出更多信息

![image-20241030133532448](./ysyxnote.assets/image-20241030133532448.png)

#### 改进2: 输出库函数错误原因

![image-20241030134033546](./ysyxnote.assets/image-20241030134033546.png)

#### 减少代码中的隐含依赖

![image-20241030134415390](./ysyxnote.assets/image-20241030134415390.png)

#### 将定义放在头文件

![image-20241030134650860](./ysyxnote.assets/image-20241030134650860.png)

# 搭建verilator仿真环境

安装参考：https://verilator.org/guide/latest/install.html

```
# Prerequisites:
#sudo apt-get install git help2man perl python3 make autoconf g++ flex bison ccache
#sudo apt-get install libgoogle-perftools-dev numactl perl-doc
#sudo apt-get install libfl2  # Ubuntu only (ignore if gives error)
#sudo apt-get install libfl-dev  # Ubuntu only (ignore if gives error)
#sudo apt-get install zlibc zlib1g zlib1g-dev  # Ubuntu only (ignore if gives error)

git clone https://github.com/verilator/verilator   # Only first time

# Every time you need to build:
unsetenv VERILATOR_ROOT  # For csh; ignore error if on bash
unset VERILATOR_ROOT  # For bash
cd verilator
git pull         # Make sure git repository is up-to-date
git tag          # See what versions exist
#git checkout master      # Use development branch (e.g. recent bug fixes)
#git checkout stable      # Use most recent stable release
#git checkout v{version}  # Switch to specified release version

autoconf         # Create ./configure script
./configure      # Configure and create Makefile
make -j `nproc`  # Build Verilator itself (if error, try just 'make')
sudo make install

```

示例demo：https://itsembedded.com/dhd/verilator_1/

# 参考资料

第六期https://ysyx.oscc.cc/docs/

https://blog.sciencenet.cn/blog-414166-562616.html

busybox工具：https://www.busybox.net/

coreutils：https://www.gnu.org/software/coreutils/

包搜索页面：https://packages.ubuntu.com/

c语言标准手册：
	c90:https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf

​        c99:https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf

qemu参考链接：

https://blog.csdn.net/fontthrone/article/details/104157859

riscv指令手册：https://github.com/riscv/riscv-isa-manual

[认识RISC-V指令集并搭建实验环境](https://blog.csdn.net/qq_61653333/article/details/138308612)