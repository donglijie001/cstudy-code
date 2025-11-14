参考资料：https://safari.ethz.ch/courses/

# DDCAETH

## p0 Introduction and basics

![image-20250203204502758](./digitalDesignAndComputerArchitecture.assets/image-20250203204502758.png)

![image-20250203204821469](./digitalDesignAndComputerArchitecture.assets/image-20250203204821469.png)

![image-20250204160823301](./digitalDesignAndComputerArchitecture.assets/image-20250204160823301.png)

![image-20250204161041719](./digitalDesignAndComputerArchitecture.assets/image-20250204161041719.png)

![image-20250204162322247](./digitalDesignAndComputerArchitecture.assets/image-20250204162322247.png)

![image-20250204170706091](./digitalDesignAndComputerArchitecture.assets/image-20250204170706091.png)

## lecture2

a：阅读任务：ddca 第一章， introduction to computing systems 前两章

b：阅读任务：

<img src="./digitalDesignAndComputerArchitecture.assets/image-20250209162228485.png" alt="image-20250209162228485" style="zoom:50%;" />

非门

![image-20250209171211307](./digitalDesignAndComputerArchitecture.assets/image-20250209171211307.png)

非门使用了两个晶体管，分别是n型和p型， n型就是输入高电压，允许电流通过，p型输入低电压允许电流通过，有个圈的是P型半导体，p型半导体比较适合拉高电压。

与非门

![image-20250209172231164](./digitalDesignAndComputerArchitecture.assets/image-20250209172231164.png)

![image-20250209172333468](./digitalDesignAndComputerArchitecture.assets/image-20250209172333468.png)

与门

![image-20250209172547089](./digitalDesignAndComputerArchitecture.assets/image-20250209172547089.png)

总结：非门、与非门、与门

![image-20250217133658840](./digitalDesignAndComputerArchitecture.assets/image-20250217133658840.png)

![image-20250217135113473](./digitalDesignAndComputerArchitecture.assets/image-20250217135113473.png)

如下图，在给定时间，一个网络是开，那另一个网络就必须是关，如果同时开启的话，就会造成短路，如果同时关闭的话，就会造成浮动，会出现未定义行为（也叫z value）。

![image-20250217135139499](./digitalDesignAndComputerArchitecture.assets/image-20250217135139499.png)

Power Consumption

![image-20250222191535720](./digitalDesignAndComputerArchitecture.assets/image-20250222191535720.png)

动态功耗：晶体管1和0之间相互变换。静态功耗：电路本身就会消耗一些能量。

Combinational Building Blocks（组合构件）

Decoder

解码器实际上生成了函数的最小项

![image-20250223151712700](./digitalDesignAndComputerArchitecture.assets/image-20250223151712700.png)

![image-20250223160646748](./digitalDesignAndComputerArchitecture.assets/image-20250223160646748.png)

MUX

![image-20250223160926452](./digitalDesignAndComputerArchitecture.assets/image-20250223160926452.png)

mux可以当作查找表来用。

Full Adder

![image-20250223163406857](./digitalDesignAndComputerArchitecture.assets/image-20250223163406857.png)

![image-20250223163537265](./digitalDesignAndComputerArchitecture.assets/image-20250223163537265.png)

Programmable Logic Array (PLA)

![image-20250223185558982](./digitalDesignAndComputerArchitecture.assets/image-20250223185558982.png)

pla 就是可编程逻辑阵列，就是实现一个逻辑函数，首先要有输入，n个输入，对应2^n个与门，每一个与门都是minterm，从上到下依次排开，输出就是或门，几个输出就有几个或门，一个输出对应一个函数F，F就可以由这些输入的minterm组合而成，实际上就是或运算，或运算相当于就是这些minterm给连接起来，怎么连这些minterm，就是pla。

Logic Completeness

![image-20250301122921200](./digitalDesignAndComputerArchitecture.assets/image-20250301122921200.png)

## lecture3

Comparator

![image-20250301125042803](./digitalDesignAndComputerArchitecture.assets/image-20250301125042803.png)

ALU

![image-20250301125412578](./digitalDesignAndComputerArchitecture.assets/image-20250301125412578.png)

Tri-State Buffer

![image-20250301142000835](./digitalDesignAndComputerArchitecture.assets/image-20250301142000835.png)

![image-20250301142440930](./digitalDesignAndComputerArchitecture.assets/image-20250301142440930.png)

同一时刻cpu和内存只能有一个可以连接到总线

Logic Simplification(组合逻辑简化)

这个比较好用的就是卡特图

![image-20250301143416162](./digitalDesignAndComputerArchitecture.assets/image-20250301143416162.png)

下面这个例子更复杂

![image-20250301143616967](./digitalDesignAndComputerArchitecture.assets/image-20250301143616967.png)

![image-20250301145958861](./digitalDesignAndComputerArchitecture.assets/image-20250301145958861.png)

时序逻辑：

双稳态原件：Q为0或1，但是设置状态的机制。

有一种不稳定状态，就是输出在0和1之间。

![image-20250301153508266](./digitalDesignAndComputerArchitecture.assets/image-20250301153508266.png)

SR latch：

既可以用与非门也可以用异或门实现，如下图，S和R的位置不一样

<img src="./digitalDesignAndComputerArchitecture.assets/image-20250301160355067.png" alt="image-20250301160355067" style="zoom:50%;" />

![image-20250301160839260](./digitalDesignAndComputerArchitecture.assets/image-20250301160839260.png)

使用NAND实现的SR，R和S 不可以同时为0，而使用异或门实现的SR，R和S不能同时为1.

Dlatch

![image-20250301162318807](./digitalDesignAndComputerArchitecture.assets/image-20250301162318807.png)

Register

![image-20250301162523217](./digitalDesignAndComputerArchitecture.assets/image-20250301162523217.png)

Memory

![image-20250301165520703](./digitalDesignAndComputerArchitecture.assets/image-20250301165520703.png)

![image-20250301165735742](./digitalDesignAndComputerArchitecture.assets/image-20250301165735742.png)

![image-20250301170132397](./digitalDesignAndComputerArchitecture.assets/image-20250301170132397.png)

![image-20250301182541245](./digitalDesignAndComputerArchitecture.assets/image-20250301182541245.png)

State：

![image-20250301190609613](./digitalDesignAndComputerArchitecture.assets/image-20250301190609613.png)

![image-20250301190706594](./digitalDesignAndComputerArchitecture.assets/image-20250301190706594.png)

FSM

![image-20250301192856062](./digitalDesignAndComputerArchitecture.assets/image-20250301192856062.png)

<img src="./digitalDesignAndComputerArchitecture.assets/image-20250301193114241.png" alt="image-20250301193114241" style="zoom:50%;" />



register仅在时钟边缘发生状态变化，下面这张图，第一个时钟周期中间，input发生了变化，但是register并没有立即变化，而是等到了下一个时钟周期才发生变化。![image-20250301193409935](./digitalDesignAndComputerArchitecture.assets/image-20250301193409935.png)

register 使用Dlatch存在问题，因此有了触发器。

![image-20250301194250990](./digitalDesignAndComputerArchitecture.assets/image-20250301194250990.png)

![image-20250301194625067](./digitalDesignAndComputerArchitecture.assets/image-20250301194625067.png)

## lectur5

FSM

![image-20250302141125714](./digitalDesignAndComputerArchitecture.assets/image-20250302141125714.png)

Demo:交通指示灯

![image-20250302141610247](./digitalDesignAndComputerArchitecture.assets/image-20250302141610247.png)

设计状态机的时候，必须要有一个reset状态。

![image-20250302141627153](./digitalDesignAndComputerArchitecture.assets/image-20250302141627153.png)

![image-20250302145626902](./digitalDesignAndComputerArchitecture.assets/image-20250302145626902.png)

![image-20250302151018721](./digitalDesignAndComputerArchitecture.assets/image-20250302151018721.png)

![image-20250302151437030](./digitalDesignAndComputerArchitecture.assets/image-20250302151437030.png)

![image-20250302151906472](./digitalDesignAndComputerArchitecture.assets/image-20250302151906472.png)

![image-20250302151932326](./digitalDesignAndComputerArchitecture.assets/image-20250302151932326.png)

状态编码：有三种类型

![image-20250302153041146](./digitalDesignAndComputerArchitecture.assets/image-20250302153041146.png)

![image-20250302153202877](./digitalDesignAndComputerArchitecture.assets/image-20250302153202877.png)

![image-20250302153652409](./digitalDesignAndComputerArchitecture.assets/image-20250302153652409.png)

![image-20250302154306795](./digitalDesignAndComputerArchitecture.assets/image-20250302154306795.png)

Verilog

![image-20250302171904338](./digitalDesignAndComputerArchitecture.assets/image-20250302171904338.png)

![image-20250302171957472](./digitalDesignAndComputerArchitecture.assets/image-20250302171957472.png)

定义多位输入和输出

![image-20250302172143542](./digitalDesignAndComputerArchitecture.assets/image-20250302172143542.png)

![image-20250302172348404](./digitalDesignAndComputerArchitecture.assets/image-20250302172348404.png)

![image-20250302172548825](./digitalDesignAndComputerArchitecture.assets/image-20250302172548825.png)

这里使用了verilog ，参考书籍：轻松成为设计高手-VERILOGHDL实用精解

194页DDCA 硬件描述语言

## Verilog 笔记 

verilog有三种基本的描述方法：

- 数据流描述：采用assign语句
- 行为描述：使用always或init 语句块
- 结构化描述：实例化已有的功能模块

结构化描述主要有以下三种：

- Module实例化：实例化以后的module
- 门实例化：实例化基本的门电路原语
- 用户定义原语(UDP)实例化：实例化用于定义的原语

模块定义：

![image-20250304220040066](./digitalDesignAndComputerArchitecture.assets/image-20250304220040066.png)

模块定义实际上可以两种方式。

![image-20250304220448277](./digitalDesignAndComputerArchitecture.assets/image-20250304220448277.png)

当输入有多个位时，[range_end : range_start]，高位写在左边，低位写在右边，语句声明的顺序如下：

![image-20250304220827042](./digitalDesignAndComputerArchitecture.assets/image-20250304220827042.png)

Verilog编译指令：

![image-20250304221550909](./digitalDesignAndComputerArchitecture.assets/image-20250304221550909.png)

或者遇到resetall也行。

Z： High impedance state ,相当于是开路。

表示数字：

![image-20250308201535586](./digitalDesignAndComputerArchitecture.assets/image-20250308201535586.png)

表示数字有多少位，这个不是必须的，数值可以指明位宽，也可以不指明位宽，不指明位宽时，一般默认为32bit。

![image-20250308201615808](./digitalDesignAndComputerArchitecture.assets/image-20250308201615808.png)

在Verilog中，负数通常在位宽数字前加一个减号表示。比如-6'd15， 这是指6位的十进制-15.



在[verilog练习网站](https://hdlbits.01xz.net/wiki/Step_one)上练习的第一道题，答案是：`assign one = 1'b1;`

### Wire

直通，表示连线，输入有变化，输出马上无条件反应，我的感觉就是一个导线，电阻为0.

```
assign     LHS_target = RHS_expression  ；
assign 为关键词，任何已经声明 wire 变量的连续赋值语句都是以 assign 开头
LHS（left hand side） 指赋值操作的左侧，RHS（right hand side）指赋值操作的右侧。
```

verilog 中module声明时的input和output，没有特别说明的话，就可以认为是wire。

![image-20250315162331952](./digitalDesignAndComputerArchitecture.assets/image-20250315162331952.png)

上面这个说了，input wire a 和input a是一样的。assign 语句只是把两个wire 连接到一起，并不创建wire。

“！”表示逻辑求反，“~”表示按位求反。

## lecture 6

always 中变量类型必须是reg类型，并且不能使用assign。

同步和异步reset

![image-20250316150359056](./digitalDesignAndComputerArchitecture.assets/image-20250316150359056.png)

在always语句块中，可以使用begin-end 语句块。

![image-20250316150726100](./digitalDesignAndComputerArchitecture.assets/image-20250316150726100.png)

always使用总结。

![image-20250316152802570](./digitalDesignAndComputerArchitecture.assets/image-20250316152802570.png)

非阻塞赋值和阻塞赋值

![image-20250316161702773](./digitalDesignAndComputerArchitecture.assets/image-20250316161702773.png)

#### Implicit nets

可以使用``default_nettype none` 来减少bug的产生。

```
逻辑或 ||
按位或 ｜
按位取反～
拼接操作符：{}
always：有讲到循环https://hdlbits.01xz.net/wiki/Vectorr
重复的操作运算符：{num{vector}}，类似于拼接，它解决的是像这种：a = {b,b,b,b,b,b}
比如{2{a,b,c}}          // The same as {a,b,c,a,b,c}
同或:~^ 相同为1，不同为0。
```



# 1From Zero to One

## Number Systems

十进制

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241106133404731.png" alt="image-20241106133404731" style="zoom:25%;" />

二进制

十六进制

  **Bytes, Nibbles, and All That Jazz**

```
一个字节8位，byte
4位，半个字节：nibble

```

**words**

```
处理器处理数据的单位，
```

**lsb msb LSB MSB**

小写的lsb 和msb是指位，而大写的LSB和MSB是指字节。

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241106134631842.png" alt="image-20241106134631842" style="zoom:50%;" />

K、M 、G的快捷运算。

![image-20241106135058906](./digitalDesignAndComputerArchitecture.assets/image-20241106135058906.png)

**有符号二进制数**

1、原码（Sign-Magnitude）：原码是将负数的符号位设为1，并将数值部分表示为该负数的绝对值的二进制形式。例如，-5的原码为10000101。

2、补码（Two's Complement）：补码是将负数的绝对值表示为二进制形式后，再对其取反（将1换为0，0换为1），并加上1。即，负数的补码为其对应正数的反码加1。例如，-5的补码为11111011。

- 反码定义：**正数的反码等于其原码，负数的反码是其原码除符号位外，按位取反。**
- 补码定义：**正数的补码等于其原码，负数的补码是其反码加1。**

[补码反码](https://www.cnblogs.com/codeshell/p/14023387.html)

根据补码求原码

正数原码、补码、反码都一样。

负数：

原码->补码： 除符号位以外，原码取反以后，加1.

补码->原码：除符号位以外，补码取反以后，加1.

求补码case：

比如-2的原码1010，忽略符号位，取反后，1101，加1变成1110。但是书上给的case，是这么算的，如果把-2求绝对值，对应的二进制数是0010，取反，1101，加1变成1110。

补码求原码case：

1001是补码，取反0110，加1是0111，对应10进制是7，首先这肯定是个负数，因此是-7，这是书上写的。

或者忽略符号位，取反，1110，加1是1111，对应十进制就是-7，感觉比书上更简单一些。



## Logic Gates





| gate‘s name                           | Demo                                                         |
| ------------------------------------- | ------------------------------------------------------------ |
| NOT                                   | <img src="./digitalDesignAndComputerArchitecture.assets/image-20241107133711776.png" alt="image-20241107133711776" style="zoom: 50%;" /> |
| Buffer(缓冲器，类似一个电线)          | <img src="./digitalDesignAndComputerArchitecture.assets/image-20241107133820247.png" alt="image-20241107133820247" style="zoom:50%;" /> |
| AND                                   | <img src="./digitalDesignAndComputerArchitecture.assets/image-20241107134129574.png" alt="image-20241107134129574" style="zoom:50%;" /> |
| OR                                    | <img src="./digitalDesignAndComputerArchitecture.assets/image-20241107134222180.png" alt="image-20241107134222180" style="zoom:50%;" /> |
| XOR（exclusive or）                   | <img src="./digitalDesignAndComputerArchitecture.assets/image-20241107134619763.png" alt="image-20241107134619763" style="zoom:50%;" /> |
| NAND(not and) 和and 正好相反          | <img src="./digitalDesignAndComputerArchitecture.assets/image-20241107134519148.png" alt="image-20241107134519148" style="zoom:50%;" /> |
| NOR（not or）和or相反                 | <img src="./digitalDesignAndComputerArchitecture.assets/image-20241107134707678.png" alt="image-20241107134707678" style="zoom:50%;" /> |
| XNOR（XOR取反，输入相同为1，否则为0） | <img src="./digitalDesignAndComputerArchitecture.assets/image-20241107135024505.png" alt="image-20241107135024505" style="zoom:50%;" /> |

多输入逻辑门有N-input AND、N-input OR。

多输入逻辑与门是当所有的输入都为true，输出才会true，多输入逻辑或门是至少有一个输入为true，输出就为true。多输入逻辑NOR，当所有的输入都为false的时候输出为true，否则为false，这个的结果实际上是多输入OR门取反。

## Logic Levels

![image-20241108134227246](./digitalDesignAndComputerArchitecture.assets/image-20241108134227246.png)

driver 输出LOW(0) ,当输入在0～$V_{ol}$之间。

​       输出HIGH(1),当输出在$V_{OH}$～ $V_{DD}$之间。

reciever 输出LOW，当输入在0~${V_{IL}}$ 之间

​	 输出HIGH，当输入在$V_{IH}$～ $V_{DD}$之间。

NM (noise margin) 噪声边缘。噪声在电路里，一般会使高电压降低，低电压升高。

# Combinational Logic Design 

![image-20241110174021624](./digitalDesignAndComputerArchitecture.assets/image-20241110174021624.png)

上面的CL放一起的标记表示这个电路全都是组合逻辑实现的。

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241110200101332.png" alt="image-20241110200101332" style="zoom:50%;" />

在上面的a图中，为了简化画图，一条横线用来表示bus，数字表示有多少个输入和输出。如果输入和输出的个数不重要，就可以把数字省略。

电路如果是组合电路需要满足的条件：

1、每个组合电路的元素都必须是组合电路

2、电路的每个结点要么是电路的输入，要么是电路的输出。

3、电路不包含循环路径，通过电路的每条路径最多访问一个电路节点一次。





product：乘积，对多个布尔变量进行与运算，也叫蕴含项（implicant），比如下面的
$$
\bar{A}B,A\bar{B}C
$$


minterm：所有输入的product，且输入的变量只出现一次，比如ABC 

maxterm：所有输入的和，且输入的变量只出现一次，比如A+B+C

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241109130018209.png" alt="image-20241109130018209" style="zoom:50%;" />

也就是说函数可以由minterm组成。这个怎么来的呢，首先，是要有一个Canonical SOP Form（规范的sop表格），比如下面这张图，按照顺序，从上到下是每个输入对应的minterm，当输入为0的时候，对应的minterm计算的时候，就是要取反，比如m0，ABC的输入值都为0，所以minterm为对应的输入都取反。

![image-20250223174445317](./digitalDesignAndComputerArchitecture.assets/image-20250223174445317.png)



**sop（sum of prodcuts）**:极小项的和，这里的每一个极小项的值都是1。

![image-20250223131007139](./digitalDesignAndComputerArchitecture.assets/image-20250223131007139.png)

**pos（produt of sum）**：极大项的乘积，这里的每一个极大项的值都是0，为0的意思就是根据真值表的输入，让对应的输出Y为0，比如下图，当A=0，B=0的时候，Y为0，maxterm就是A+B，当A=0，B=1的时候，Y为0的话maxterm就是$A+\bar{B}$，然后最后就输出函数Y还是把所有Y值为0的maxterm乘一起就是最终的结果。

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241113135948483.png" alt="image-20241113135948483" style="zoom:50%;" />

![image-20250223145545030](./digitalDesignAndComputerArchitecture.assets/image-20250223145545030.png)

![image-20250223150155158](./digitalDesignAndComputerArchitecture.assets/image-20250223150155158.png)

## 布尔代数的一些定理

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241109141929044.png" alt="image-20241109141929044" style="zoom:50%;" />

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241109141944872.png" alt="image-20241109141944872" style="zoom:50%;" />

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241109142047373.png" alt="image-20241109142047373" style="zoom:50%;" />

[中文版参考链接](https://blog.csdn.net/weixin_44997802/article/details/106292752)

## 原理图schematic

数字电路的示意图，显示元件和连接元件的导线。

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241110202111480.png" alt="image-20241110202111480" style="zoom:50%;" />

画原理图的一般准则：

- 输入在原理图的左边或者上边
- 输出在原理图的右边或者下边
- 只要可能的话，门应该从左向右流动
- 使用直角线，不要使用弯曲的线
- 导线总是以T型连接
- 导线交叉处的点表示导线之间的连接
- 没有圆点的导线交叉不构成连接

mux（多路选择器）

比如一个4:1 mux，代表一个4输入，1输出的多路选择器。

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241110210736279.png" alt="image-20241110210736279" style="zoom:50%;" />

对应的结果如下图。

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241110210758158.png" alt="image-20241110210758158" style="zoom:50%;" />

可以用mux来实现某些逻辑门，比如与门

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241110210902906.png" alt="image-20241110210902906" style="zoom:50%;" />

上面这张图里，先是真值表，下面是mux，AB就是select，当AB的输入值为00，01，10的时候，对应的Y预期应该为0，而在mux中，对应的输出为D0、D1、D2，所以D0、D1、D2的值为0，这里用接地表示0。

**decoder**

n个输入$2^N$个输出，每个输出里面只有一位为1，其他都是0。

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241111132409095.png" alt="image-20241111132409095" style="zoom:50%;" />

把上面这个decoder用与门和非门实现，如下图，这个实际上就是根据真值表，找到对应为1的minterm，比如Y3就是$A_0 *A_1$

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241111133105209.png" alt="image-20241111133105209" style="zoom:50%;" />

然后也可以用2:4 Decoder和一个或门，组成一个与非门，因为2:4Decoder的输出从Y3到Y0，就是minterm，然后与非门关系式就是：$Y=\bar{A}\bar{B} + AB$，正好对应Y3和Y0的输出结果。

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241111134706947.png" alt="image-20241111134706947" style="zoom:50%;" />

 **TIMING（定时）**

如下图，输出需要一定的时间才能响应输入的变化。下面这张图，叫时序图，瞬态响应从低到高的转换称为上升沿，从高到低称为下降沿。测量延迟是从input上升到50%开始，到output上升到50%结束。

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241111135415716.png" alt="image-20241111135415716" style="zoom:50%;" />

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241111215058413.png" alt="image-20241111215058413" style="zoom:50%;" />

Propagation and Contamination Delay

数字电路的延迟分为两个部分，一个是传输时延，一个是晶体管输入端旧状态消失到输出端旧状态消失的时延。

tpd为晶体管输入端进入新状态出现到输出端进入新状态的延迟。

tcd 是从任何输入发生变化到任何输出开始改变其值的最短时间，从上面图看的话，就是从input上升到50%，然后ouput上升到50%的时间。

[有关延迟可以看这个](http://m.kcjyyj.com/view.php?aid=7066)

组合电路的传播延迟是通过关键路径上每个元件的传播延迟之和。污染延迟是通过短路径上每个元件的污染延迟之和。这些延迟如图 2.69 所示，并由以下方程式描述，下面这两个公式仅仅对2.69的图生效。

**最短路径**指的是组合逻辑电路中从输入端到输出端变化最快的路径。**关键路径**是指组合逻辑电路中从输入端到输出端变化最慢的路径。

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241112134109721.png" alt="image-20241112134109721" style="zoom:50%;" />

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241112134312947.png" alt="image-20241112134312947" style="zoom:50%;" />

求传输时延就是关键路径上的每一个元器件的tpd的和，污染时延（contamination delay）就是最短路径上的每个元器件的tcd的和。



比如下图这样一个mux的逻辑实现图，不同的实现，对应 tpd是不一样的，

如果数据输入在控制输入之前到达，我们更喜欢具有最短控制到输出延迟的设计（图 2.74 中的分层设计）。同样，如果控制输入在数据输入之前到达，我们更喜欢具有最短数据到输出延迟的设计（图 2.73(b) 中的三态设计）。

最佳选择不仅取决于电路中的关键路径和
输入到达时间，还取决于零件的功率、成本和可用性

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241112135859992.png" alt="image-20241112135859992" style="zoom:50%;" />

## glitches（故障）

这张图

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241112222407402.png" alt="image-20241112222407402" style="zoom:50%;" />

当A=0，C=1的时候，B从1变成0，会有故障，但最终Y的输出值是符合预期的。

因为B从1变成0，n2那条线会线先从1变成0，这个时候，n1的输入从0变成1，没有n2变得快，所以，这个时候Y的输出是0，然后最终Y会变成1。

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241112222421547.png" alt="image-20241112222421547" style="zoom:50%;" />

要解决这个问题。可以加一个冗余，就可以解决问题了。

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241112222725499.png" alt="image-20241112222725499" style="zoom:50%;" />

一般来说，当单个变量的变化跨越 K-map 中两个主要蕴涵项之间的边界时，就会出现故障。

这句话我不是太理解，从字面意义上来说看应该是下面，B从0变成1，分别是在两个蕴含项之间。

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241112224422085.png" alt="image-20241112224422085" style="zoom:50%;" />

# Sequential Logic Design

183页：习题开始：

**state**：状态包含了电路未来行为所需的所有信息。

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241128215926083.png" alt="image-20241128215926083" style="zoom:50%;" />

**Synchronous Sequential Circuits** ：是一种使用触发器的时序电路，共享同一个公共时钟。

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241128220944295.png" alt="image-20241128220944295" style="zoom:50%;" />

##  LATCHES AND FLIP-FLOPS

双稳态元件（bistable element）的简单组成如下，使用两个反向器组成。

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241122001755806.png" alt="image-20241122001755806" style="zoom:50%;" />

a和b的功能是一样的。这个电路是没有inputs。但是有两个输出。$Q和\bar{Q}$。这个交叉耦合反相器具有两个稳定状态，$Q=0$和$\bar{Q}=1$，还有第三种状态就是两个输出大约位于0和1之间。

具有 N 个稳定状态的元件传达 $log_2N$ 位信息，因此双稳态元件存储一位信息。这个双稳态元件，保存的信息永远不变，如果$Q$是0，那它会永远保持0，如果$Q$是1，那它会永远保持1。但是这个好像在实际生产中并不会使用，因为它没有输入去控制状态。

###  SR Latch

由两个对称耦合的NOR门组成。

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241122130931789.png" alt="image-20241122130931789" style="zoom:50%;" />

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241122131951263.png" alt="image-20241122131951263" style="zoom:50%;" />

如上图，当S和R都为0的时候，$Q和\bar{Q}$的值取决于它之前的值。S是set，R是reset。S设为1的时候Q为1，$\bar{Q}$为0，R为1的时候，Q为0，$\bar{Q}$为1，R和S不会同时设置，因为没有任何意义，在一个电路里，不会同时置位和重置，当R和S都不设置的时候，$Q和\bar{Q}$会记住之前的值，不会发生变化。

下图是SR的示意图。

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241122133712985.png" alt="image-20241122133712985" style="zoom:50%;" />

###  D Latch

SR锁存器比较笨拙，当S和R都置为1的时候，会发生意想不到的问题，并且S和R输入混淆了什么时候设置和何时设置的问题（英文并不是这么写的，这是我的理解）。

CLK：控制何时输出改变

D：输入的数据

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241122134159643.png" alt="image-20241122134159643" style="zoom:50%;" />

当CLK为0的时候，无论D为何值，$Q和\bar{Q}$都会记住之前的值，这样就避免了SR锁存器中，S和R同时为1的情况。

当CLK为1的时，锁存器就是透明的，D为何值，Q就会何值，当CLK为0的时候，Q保留旧值。

###  D FIip-Flop（D 触发器）

D触发器由两个D锁存器构成，如下图：

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241122135602504.png" alt="image-20241122135602504" style="zoom:50%;" />

D触发器在时钟的上升沿（输入信号从0变成1）将输入信号D复制到Q，并在其他所有的时间，记住这个状态。D触发器又称为边缘触发器，符号中的三角形表示边沿触发时钟输入。

### Register

N位寄存器是由一组N个触发器组成，这些触发器使用同一个公共的CLK输入。下图是一个4位的寄存器。

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241122222519868.png" alt="image-20241122222519868" style="zoom:30%;" />

###  Enabled Flip-Flop（使能触发器）

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241122222821004.png" alt="image-20241122222821004" style="zoom:50%;" />

EN为TRUE时， Enabled Flip-Flop和普通的D触发器一样，当 EN 为 FALSE 时，使能触发器忽略时钟并保持其状态，当我们希望只在某些时候而不是在每个时钟边沿将新值加载到触发器中时，Enabled Flip-Flop很有用。

注意：当CLK为1时，EN不能改变，否则会触发时钟故障。

###  Resettable Flip-Flop

可复位触发器，增加了另外一个输入Reset，当Reset为False的时候，可复位触发器和D触发器一样，当Reset为True的时候，可复位触发器忽略D，并将输出复位为0，

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241123220357147.png" alt="image-20241123220357147" style="zoom:50%;" />

可复位触发器有同步的也有异步的，需要自己去设计。

##  Synchronous Sequential Circuits 

同步顺序电路通常有循环路径的依赖（输出直接反馈到输入）。但是具有循环路径的顺序电路可能会出现竞争或者不稳定行为，分析这类问题，很耗费时间。为了避免这些问题，设计人员通过在路径的某个地方插入寄存器来打破循环路径。

这样就将电路变成组合逻辑和寄存器的集合，寄存器包含系统的状态，改状态仅在时钟边沿处发生变化（也可以说状态与时钟同步），

同步时序电路组成规则：

- 每个电路元件要么是寄存器，要么是组合电路
- 至少一个电路元件是寄存器
- 所有寄存器都接收相同的时钟信号
- 每个循环路径至少包含一个寄存器

D触发器是最简单的时序电路

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241124124721167.png" alt="image-20241124124721167" style="zoom:50%;" />

##  FINITE STATE MACHINES

FSM由两个组合逻辑模块（下一个状态逻辑和输出逻辑）以及存储状态的寄存器组成。

下图是一个组合逻辑，计算下一个状态，

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241129132946483.png" alt="image-20241129132946483" style="zoom:50%;" />

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241129133027114.png" alt="image-20241129133027114" style="zoom:50%;" />

状态机有M个输入，N的输出以及k位状态。

```
根据状态机的输出是否与输入条件相关来区分Moore状态机和Mealy状态机。Moore状态机：输出仅仅与当前状态有关；Mealy状态机：输出不仅取决于当前状态，还和输入有关；
```

### <img src="./digitalDesignAndComputerArchitecture.assets/image-20241124142304034.png" alt="image-20241124142304034" style="zoom:50%;" /> 

### fsm设计过程

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241129135121016.png" alt="image-20241129135121016" style="zoom:50%;" />



### FSM Design Example

交通信号灯，两个传感器$T_A和T_B$，每个传感器为True时表示有学生，为False表示没有学生，两个信号灯$L_A和L_B$。信号灯接受信号，显示红色、绿色还是黄色，时钟周期是5秒钟，在每个时钟嘀嗒声（上升沿）上，信号灯根据交通传感器的变化而变化，另外还有一个重置按钮，可以手动控制。如下图。

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241124143307229.png" alt="image-20241124143307229" style="zoom:50%;" />

状态转换图如下图：

初始态是$L_A$绿，$L_B$红，只要Academic 大道有流量，灯就不会变，$T_A$一直为true，这个对应状态$S_0$，然后再隔5秒，$L_A$变黄，然后再变红色，同样只要Bravado Blvd大道有流量，灯也不会变，$T_B$一直为true。

下图圆圈表示状态，圆弧表示状态之间的转换。转换发生在时钟的上升沿。

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241124143702803.png" alt="image-20241124143702803" style="zoom:50%;" />

3.1 是状态转移表，只要下一个状态不依赖特定输入，表格里面就使用无关符号(X)来表示，这里没有把reset给画出来。

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241124153536950.png" alt="image-20241124153536950" style="zoom:50%;" />

状态S的编码表示是表3.2，输出的编码表示是表3.3。

把状态转移表格用编码后的二进制表示如下图：

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241124155059058.png" alt="image-20241124155059058" style="zoom:50%;" />

根据上面这张表得出来下一个状态的布尔表达式。

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241124155338447.png" alt="image-20241124155338447" style="zoom:50%;" />

上面的布尔表达式还可以继续简化，比如可以使用卡特图来简化。

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241124155629708.png" alt="image-20241124155629708" style="zoom:50%;" />

上图表3.5 output和state对应的关系：

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241124160000991.png" alt="image-20241124160000991" style="zoom:50%;" />

S为00的时候，$L_A$是绿灯，$L_B$是后红灯，所以$L_A$对应的编码是00（表示绿灯），$L_B$对应的编码是10（表示红灯）

最后设计的图如下：这就是完全根据上面的状态转移方程的来的。

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241124161552706.png" alt="image-20241124161552706" style="zoom:50%;" />

###  State Encodings

只讲了[独热编码](https://blog.csdn.net/yanghaoji/article/details/123734304)，有很多位，但是同一时刻，只有一位为1。

demo：三分频计数器的设计草图（）

```
N 分频计数器有一个输出，没有输入。输出 Y 每 N 个时钟周期中有一个时钟周期为高电平。换句话说，输出将时钟频率除以 N。
```

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241125132327757.png" alt="image-20241125132327757" style="zoom:50%;" />

先写出来状态转移表

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241125132420624.png" alt="image-20241125132420624" style="zoom:50%;" />

然后是输出表

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241125132448616.png" alt="image-20241125132448616" style="zoom:50%;" />

对三个状态使用独热编码和二进制编码的对比如下表

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241125132734193.png" alt="image-20241125132734193" style="zoom:50%;" />

使用二进制编码的状态转移表如下：

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241125133146257.png" alt="image-20241125133146257" style="zoom:50%;" />

表3.9 对应的布尔表达式如下：

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241125133312709.png" alt="image-20241125133312709" style="zoom:50%;" />

使用独热编码的状态转移表如下：

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241125133635134.png" alt="image-20241125133635134" style="zoom:50%;" />

根据表3.10 得出的布尔表达式如下：

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241125133808320.png" alt="image-20241125133808320" style="zoom:50%;" />

图 3.29 显示了这些设计的示意图。请注意，二进制编码设计的硬件可以优化为 Y 和 $S'_0$ 共享相同的门。另外，请注意，独热编码需要可设置 (s) 和可重置 (r) 触发器来在重置时将机器初始化为 S0。最佳实现选择取决于门和触发器的相对成本，但对于这个特定示例，独热设计通常是更好的选择(说句实话，我不是特别理解，难道仅仅是因为独热设计用的门更少吗)。

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241125134004929.png" alt="image-20241125134004929" style="zoom:50%;" />

###  Moore and Mealy Machines 

Moore 状态机的状态转换图中，输出用圆圈表示，在Mealy 状态机的状态转换图中，输出用弧线标记，如下图中的b所示

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241125135842344.png" alt="image-20241125135842344" style="zoom:50%;" />

demo：蜗牛爬行，每个时钟周期，蜗牛都会爬到下一个比特，当它爬过的最后两位是01时，蜗牛会微笑，输入A是蜗牛触角下面的位，当蜗牛微笑时，输出Y为True，分别使用Moore和Mealy状态机设计，为每格机器绘制时序图，显示蜗牛沿0100110111爬行时的输入、状态和输出。

Moore FSM

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241127133741459.png" alt="image-20241127133741459" style="zoom:50%;" />

Mealy FSM（153页） 如上右图，只需要两个状态，每条弧都标记为A/Y，A是导致该转换的输入值，Y是对应的输出。Mealy FSM组合状态转换如下图，



<img src="./digitalDesignAndComputerArchitecture.assets/image-20241128133419266.png" alt="image-20241128133419266" style="zoom:50%;" />

Mealy 机只需要一位状态。考虑使用二进制状态编码：S0 = 0 和 S1 = 1。表 3.16 使用这些编码重写了状态转换和输出表。

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241128133843395.png" alt="image-20241128133843395" style="zoom:50%;" />

moore 的状态转移表如下：

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241202131620080.png" alt="image-20241202131620080" style="zoom:50%;" />

得出状态转移方程：

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241202132710235.png" alt="image-20241202132710235" style="zoom:50%;" />

Mealy的状态转移表

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241202131755073.png" alt="image-20241202131755073" style="zoom:50%;" />

得出状态转移方程：

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241202132809435.png" alt="image-20241202132809435" style="zoom:50%;" />

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241202133101181.png" alt="image-20241202133101181" style="zoom:50%;" />



![image-20241202133517444](./digitalDesignAndComputerArchitecture.assets/image-20241202133517444.png)

在mealy状态机中，一旦输入变为1，就会立即发生响应，而在moore 状态机中，需要到下一个时钟边沿才会发生变化。

 

### Factoring State Machines 

状态机分解，将复杂的FSM分解为多个交互的更简单的状态机设计会变得更容易。

### Deriving an FSM from a Schematic

```
从原理图导出状态转换图几乎遵循 FSM 设计的逆过程。例如，在接手一个文档不完整的项目或对其他人的系统进行逆向工程时，此过程可能是必要的。
▸检查电路，说明输入、输出和状态位。
▸编写下一个状态和输出方程。
▸创建下一个状态和输出表。
▸减少下一个状态表以消除无法到达的状态。
▸为每个有效的状态位组合分配一个名称。
▸用状态名称重写下一个状态和输出表。
▸绘制状态转换图。
▸用文字说明 FSM 的作用。
```

Demo:

直接看书上的demo吧，清晰易懂

##  TIMING OF SEQUENTIAL LOGIC

触发器在时钟的上升沿将输入 D 复制到输出 Q。此过程称为在时钟沿对 D 进行采样。如果时钟上升时 D 稳定在 0 或 1，则此行为定义明确。但如果 D 在时钟上升的同时发生变化，会发生什么情况？

书上举了一个青蛙从荷叶上跳水的例子，说明了顺序元件在时钟沿附近有一个光圈时间（aperture time），在此期间，输入必须稳定，触发器才能产生明确的输出。

aperture time 是由setup time和hold time决定的，分别在时钟沿之前和之后。

#### Input Timing Constraints

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241211135005078.png" alt="image-20241211135005078" style="zoom:50%;" />

setuptime实际上是D到N1得时间，

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241211135433399.png" alt="image-20241211135433399" style="zoom: 25%;" />

holdTime实际上是反相器的延迟

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241211135556082.png" alt="image-20241211135556082" style="zoom:25%;" />

#### Output Timing Constraints

tpcq和tccq

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241212131534096.png" alt="image-20241212131534096" style="zoom:50%;" />

输出时序约束是指时钟边沿之后，输出Q变化所需的时间，

tpcq 实际上就是L2的最大延迟。

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241212132218157.png" alt="image-20241212132218157" style="zoom: 25%;" />

####  The Dynamic Discipline（动态规则）

为了使电路能够正确地采样输入，电路的输入比如在时钟上升沿之前稳定一段时间，称为$t_{setup}$，在时钟沿上升之后，也要稳定一段时间，称为$t_{hold}$。这两个时间加一起，是输入必须保持稳定的总时间（孔径时间）。

动态原则规定，同步时序电路的输入在时钟边沿的建立和保持孔径时间内必须保持稳定。因为这个规则，我们可以保证触发器在信号不变的情况下对其进行采样，因为，我们只关心采样时输入的最终值，所以我们可以将信号视为时间上和逻辑层面上的离散信号。

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241211131921415.png" alt="image-20241211131921415" style="zoom:50%;" />

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241212133028948.png" alt="image-20241212133028948" style="zoom:50%;" />



####  System Timing（系统时序）

$T_{c}$:时钟周期，时钟上升沿之间的时间。

$f_c = 1/{T_c}$，时钟的频率。

1MHz=$10^{6}$Hz

1GHz=$10^{9}$Hz

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241211131947447.png" alt="image-20241211131947447" style="zoom:50%;" />

在时钟的上升沿，寄存器 R1 产生输出（或输出）Q1。这些信号进入组合逻辑块，产生 D2，即寄存器 R2 的输入（或输入）

图 3.38(b) 中的时序图显示，每个输出信号可能在其输入改变后开始改变污染延迟，并在其输入稳定后的传播延迟内稳定到最终值。灰色箭头表示通过 R1 和组合逻辑的污染延迟，蓝色箭头表示通过 R1 和组合逻辑的传播延迟。我们分析了与第二个寄存器 R2 的建立和保持时间相关的时序约束。

#### Setup Time Constraint

这个也叫周期时间约束(cycle time constraint)

图 3.39 是时序图，仅显示了通过路径的最大延迟，由蓝色箭头指示。为了满足 R2 的建立时间，D2 必须在不晚于下一个时钟沿之前的建立时间之前稳定下来。因此，我们找到了最小时钟周期的方程：

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241211133058822.png" alt="image-20241211133058822" style="zoom:50%;" />

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241211133937535.png" alt="image-20241211133937535" style="zoom:50%;" />

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241211133007493.png" alt="image-20241211133007493" style="zoom:50%;" />

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241212134004643.png" alt="image-20241212134004643" style="zoom:50%;" />

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241212134351998.png" alt="image-20241212134351998" style="zoom:50%;" />只有tpd是我们可以控制的。tpca+tsetup 被称为时序开销。

#### Hold Time Constraint

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241212134821577.png" alt="image-20241212134821577" style="zoom:50%;" />

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241213132245820.png" alt="image-20241213132245820" style="zoom:50%;" />

我突然好像明白了，由于动态规则的限制输入必须在上升沿的前后稳定一段时间，所以，同一时刻，在上升沿之后，D2经过tccq +tcd的时间会开始变化，但是为了让R2能够采集到正确的信号，在上升沿之后holdtime时间之内，D2不能发生变化，但是D2发生变化的最短时间，就是tccq+tcd，只要tccq+tcd 大于$t_{hold}$，那么，上升沿之后，Q1开始变化，到D2开始变化的最短时间，超过了$t_{hold}$，那么D2开始变化之前，R2就已经采集完信号了。所以就不会有问题。tcd是组合逻辑的最小时延。

#### Timing Analysis

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241213132332690.png" alt="image-20241213132332690" style="zoom:50%;" />

demo

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241228202828111.png" alt="image-20241228202828111" style="zoom:50%;" />

hold time constraint无法满足。延长最短路径，加一个缓冲器可以解决。

#### Clock Skew

时钟信号不可能同时达到所有的寄存器，

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241231134637455.png" alt="image-20241231134637455" style="zoom:50%;" />

<img src="./digitalDesignAndComputerArchitecture.assets/image-20241231134931086.png" alt="image-20241231134931086" style="zoom:50%;" />

考率倾斜时间的动态规则约束公式：

![image-20250111201301891](./digitalDesignAndComputerArchitecture.assets/image-20250111201301891.png)

![image-20250111203347798](./digitalDesignAndComputerArchitecture.assets/image-20250111203347798.png)

#### Metastability

当输入信号在采样窗口时间内发生变化时，会发生亚稳态，

![image-20250111203800979](./digitalDesignAndComputerArchitecture.assets/image-20250111203800979.png)

<img src="./digitalDesignAndComputerArchitecture.assets/image-20250111204700112.png" alt="image-20250111204700112" style="zoom:50%;" />

Case3 是有可能出问题的。

![image-20250112112317850](./digitalDesignAndComputerArchitecture.assets/image-20250112112317850.png)

亚稳态在任何时候我们有一个双稳态器件时都会发生，触发器进入亚稳态会停留不确定的时间，

![image-20250112113247245](./digitalDesignAndComputerArchitecture.assets/image-20250112113247245.png)

![image-20250112113347493](./digitalDesignAndComputerArchitecture.assets/image-20250112113347493.png)

#### Parallelism

![image-20250112115828359](./digitalDesignAndComputerArchitecture.assets/image-20250112115828359.png)

![image-20250112115929771](./digitalDesignAndComputerArchitecture.assets/image-20250112115929771.png)

![image-20250112120032639](./digitalDesignAndComputerArchitecture.assets/image-20250112120032639.png)

![image-20250112120118103](./digitalDesignAndComputerArchitecture.assets/image-20250112120118103.png)

![image-20250112120236078](./digitalDesignAndComputerArchitecture.assets/image-20250112120236078.png)

![image-20250112120355079](./digitalDesignAndComputerArchitecture.assets/image-20250112120355079.png)
