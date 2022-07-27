# 编译环境搭建
## 安装ubuntu虚拟机
这里我是用的vmware 安装的ubuntu20虚拟机。
```
#更新软件源以后，卸载系统自带的vim
sudo apt remove vim-common
sudo apt install vim
#安装编译工具
sudo apt-get install subversion 
sudo apt-get install g++ flex patch 
sudo apt-get install libncurses5-dev zlib1g-dev
sudo apt-get install git-core 
sudo apt-get install libssl-dev 
sudo apt-get install gawk 
# 这个在ubuntu20上找不到，暂时先不安装了。
sudo apt-get install xz-util
```
https://github.com/DarkCaster/OpenWrt-1505-Custom