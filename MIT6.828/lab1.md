# LAB1Booting a PC

## 试验主要任务

​		了解汇编语言以及Boot启动和加载内核的过程 相关控制寄存器位数的作用，最后完成一个print函数的小代码.

## 下载试验源码

```
#先创建一个目录，然后在这个目录下下载源码
mkdir mit6.828
cd mit6.828
```

使用git 下载源码的时候git报错：`symbol lookup error: /usr/lib/x86_64-linux-gnu/libhogweed.so.4: undefined symbol: __gmpn_cnd_add_n`，首先需要的解决的是ubuntu默认使用的vim不是完整版的，用起来非常难受，使用下面的命令安装完整版vim。

```
apt-get remove vim-common
apt-get install vim
```

[参考链接](https://blog.csdn.net/jiuweiljp/article/details/108213011?spm=1001.2101.3001.6650.1&utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-1-108213011-blog-107722384.235%5Ev27%5Epc_relevant_multi_platform_whitelistv3&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-1-108213011-blog-107722384.235%5Ev27%5Epc_relevant_multi_platform_whitelistv3&utm_relevant_index=2)

上个问题解决后，使用git clone的时候，又出现了新的问题。提示ssl 证书有问题，解决方案：

直接跳过ssl认证：[参考链接](https://blog.csdn.net/Areigninhell/article/details/121560737?utm_medium=distribute.pc_relevant.none-task-blog-2~default~baidujs_baidulandingword~default-4-121560737-blog-123900491.235^v27^pc_relevant_multi_platform_whitelistv3&spm=1001.2101.3001.4242.3&utm_relevant_index=7)

```
export GIT_SSL_NO_VERIFY=1
```

不知道还有没有其他的问题。

不过现在可以把文件给克隆下来了

```
git clone https://pdos.csail.mit.edu/6.828/2018/jos.git lab
cd lab
make
make qemu-nox
```

![image-20230325201242242](lab1.assets/image-20230325201242242.png)