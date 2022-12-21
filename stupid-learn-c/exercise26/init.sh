#!/bin/sh
#在"set -e"之后出现的代码，一旦出现了返回值非零，整个脚本就会立即退出
set -e
# go somewhere safe
cd /tmp

# get the source to base APR 1.4.6
curl -L -O http://archive.apache.org/dist/apr/apr-1.4.6.tar.gz

# extract it and go into the source
tar -xzvf apr-1.4.6.tar.gz
cd apr-1.4.6
# configure, make, make install
./configure
make
sudo make install

# reset and cleanup
cd /tmp
rm -rf apr-1.4.6 apr-1.4.6.tar.gz

# do the same with apr-util
curl -L -O http://archive.apache.org/dist/apr/apr-util-1.4.1.tar.gz
# extract
tar -xzvf apr-util-1.4.1.tar.gz
cd apr-util-1.4.1
# configure, make, make install
./configure --with-apr=/usr/local/apr
# you need that extra parameter to configure because
# apr-util can't really find it because...who knows.
make
sudo make install
#cleanup
cd /tmp
rm -rf apr-util-1.4.1* apr-1.4.6*
