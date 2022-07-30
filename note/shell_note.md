# shell 笔记
shell脚本的第一行是`#!/bin/bash`,告诉系统其后路径所指定的程序即是解释此脚本文件的 Shell 程序。
下面的是最简单的shell脚本程序，将其保存为test.sh。
```
#!/bin/bash
echo "Hello World !"
```
运行shell脚本有两种方法：
- 方法一：作为可执行程序
```
chmod +x ./test.sh  #使脚本具有执行权限
./test.sh  #执行脚本

注意，一定要写成 ./test.sh，而不是 test.sh，运行其它二进制的程序也一样，直接写 test.sh，linux 系统会去 PATH 里寻找有没有叫 test.sh 的，而只有 /bin, /sbin, /usr/bin，/usr/sbin 等在 PATH 里，你的当前目录通常不在 PATH 里，所以写成 test.sh 是会找不到命令的，要用 ./test.sh 告诉系统说，就在当前目录找。
```
- 方法二
```
/bin/sh test.sh
这种方式运行的脚本，不需要在第一行指定解释器信息，写了也没用。
```