#!/bin/bash
# 由于ubuntu 默认的terminal是dash，需要进行一下切换，切换到/bin/bash
# 参考链接：https://blog.csdn.net/gatieme/article/details/52136411
for integer in {1..40}
do
    ./client 127.0.0.1
done