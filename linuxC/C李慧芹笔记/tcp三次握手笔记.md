在linuxC/apue/ipc/scoket/stream/pool_static目录下，我用c写了一个c/s通过socket进行通信的demo，这里进行一下抓包，看一下tcp三次握手的内容。

[参考链接](https://juejin.cn/post/6844904070000410631)

第一次握手：

客户端给server 发送的报文里面的标志是SYN，seq=0。

![image-20240114114625147](tcp%E4%B8%89%E6%AC%A1%E6%8F%A1%E6%89%8B%E7%AC%94%E8%AE%B0.assets/image-20240114114625147.png)

第二次握手：

server端给client端发送的报文，SYN + ACK，seq=0， Ack=1，表示收到了客户端seq=0的报文。

![image-20240114115405537](tcp%E4%B8%89%E6%AC%A1%E6%8F%A1%E6%89%8B%E7%AC%94%E8%AE%B0.assets/image-20240114115405537.png)

第三次握手

客户端给server端发送的报文：ACK报文，seq =1，ack=1，表示收到了服务端发送的seq=0的报文。

![image-20240114115534743](tcp%E4%B8%89%E6%AC%A1%E6%8F%A1%E6%89%8B%E7%AC%94%E8%AE%B0.assets/image-20240114115534743.png)

然后服务端给客户端发送消息，内容是时间戳，seq =1，

![image-20240114121428583](tcp%E4%B8%89%E6%AC%A1%E6%8F%A1%E6%89%8B%E7%AC%94%E8%AE%B0.assets/image-20240114121428583.png)

然后客户端给服务端发送确认回调，然后我看到seq=1，但是ack =13， 感觉有点奇怪呀。ack = 13是因为发送的时间戳长度是12，[报文序号参考链接](https://www.cnblogs.com/xiaolincoding/p/16829073.html)，因为server端上一次给client发送报文的时候，序列号是1，

![image-20240114122419501](tcp%E4%B8%89%E6%AC%A1%E6%8F%A1%E6%89%8B%E7%AC%94%E8%AE%B0.assets/image-20240114122419501.png)

然后下面的就是四次挥手。