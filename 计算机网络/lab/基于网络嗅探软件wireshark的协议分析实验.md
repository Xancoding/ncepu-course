---
title: "基于网络嗅探软件Wireshark的协议分析实验" # 标题
date: 2022-11-12T11:38:21+08:00 # 创建时间
author: ["Xan"] # 作者
tags: # 标签
- Tech
- Wireshark
- 工具
- 新技能
- 计算机网络 
keywords: # 关键词
- Tech
- Wireshark
- 工具
- 新技能
- 计算机网络 
description: "" # 描述
weight: # 输入1可以顶置文章，用来给文章展示排序，不填就默认按时间排序
slug: ""
draft: false # 是否为草稿
comments: true # 是否展示评论
showToc: true # 显示目录
TocOpen: true # 自动展开目录
hidemeta: false # 是否隐藏文章的元信息，如发布日期、作者等
disableShare: true # 底部不显示分享栏
showbreadcrumbs: true # 顶部显示当前路径
cover:
    image: "" #图片路径 例：posts/tech/123/picture.png
    caption: "" # 图片底部描述
    alt: ""
    relative: false
---
# 概览
> **基于网络嗅探软件（wireshark）的协议分析实验**
1. Wireshark的深入学习与掌握，如过滤器的使用，归纳方法
2. 通过实验阐述ARP的工作原理
3. 利用实验结果分析ICMP协议的报文结构字段定义
4. 基于实验数据深入分析TCP协议的连接过程原理，报文的分片等功能
5. 从校园网发起向外网中某Web服务器的访问，记录并分析从MAC层协议、IP协议、TCP协议一直到HTTP协议的过程 
# 基于网络嗅探软件Wireshark的协议分析实验
## Wireshark 是什么？
> **Wirkshark 是一个功能十分强大的开源的网络数据包分析器，能够在多种平台上抓取和分析网络包**
> 
> **Wirkshark 可被用于检查安全问题和解决网络问题，也可供开发者调试协议的实现和学习网络协议的原理**
> 
> **Wireshark使用 Npcap or WinPcap 作为接口，直接与网卡进行数据报文交换**
## Wireshark 下载与安装
官网地址：<https://www.wireshark.org/>，直接点击下一步下一步安装即可
![1](https://bu.dusays.com/2022/11/12/636eef0324bca.png)
但是，我在安装过程中报了如下的错误：
![npcap](https://bu.dusays.com/2022/11/11/636e699429bad.png)
排查了好久，没找到合适的解决办法  
最后，下载 WinPcap 来代替 Npcap ，成功运行。
## Wireshark 基本用法
> 简单抓包基础步骤：选择捕获接口 -> 获取网络实时痕迹 -> 获取报文 -> 深入解析
*** 
### 选择接口（网卡）
> **网络上传输的数据包需要经过网卡到达计算机，Wireshark可以捕获流经网卡的数据包**

在使用Wireshark捕获数据前，先要选择捕获接口。一台计算机可能会有不止一个网卡，此时需要选择你要捕获数据的接口。

选择菜单栏上的 捕获->选项
![1](https://bu.dusays.com/2022/11/12/636eef03d463f.png)
选择想要捕获数据的接口后，点击开始
![2](https://bu.dusays.com/2022/11/12/636ef1eb47349.png)

### 界面说明
开始捕获后，Wireshark会把捕获到的报文显示到界面上
1. **显示过滤器**用于设置过滤条件进行数据列表区数据过滤
1. **数据列表区**展示的是Wireshark捕获到的所有数据包的列表，每个数据包包含 编号、时间戳、源地址、目标地址、协议、长度以及数据包信息
2. **数据详细区**展示的是在数据列表区中选中的数据包的分协议展示
	1. <u>Frame</u>：物理层的数据帧概况
	2. <u>Ethernet II</u>：数据链路层以太网帧头部信息
	3. <u>Internet Protocol Version 4</u>： 互联网层IP包头部信息
	4. <u>Transmission Control Protocol</u>：传输层的数据段头部信息，此处是TCP
3. **数据字节区**展示的是选中的数据包的源数据。另外，在数据详细区选中的某层或某字段，对应的数据会在数据字节区中高亮
![1](https://bu.dusays.com/2022/11/12/636efb5f7ea6d.png)

### 过滤器设置
> **根据我们想要抓取的数据包，对过滤器进行设置。过滤掉冗余的数据包，找到我们需要的信息**
#### 捕获过滤器
> **捕获过滤器表达式作用在Wireshark捕获数据包之前，只捕获符合条件的数据包**  
> 
> **当需要处理大量数据时，使用捕获过滤器可以节省大量资源**
##### 界面说明
选择菜单栏上的 捕获->捕获过滤器
![1](https://bu.dusays.com/2022/11/12/636efe3d72678.png)
点击 `+` 即可添加新的过滤规则  
 `Filter Name` 指代过滤器名称，用来给自己看该过滤器的过滤效果  
 `Filter Expression` 指代过滤器表达式，需要使用 `Berkeley Packet Filter` 语法书写
![2](https://bu.dusays.com/2022/11/12/636efe3e2ce20.png)
##### 语法规则
捕获过滤器使用 `BPF` 语法，表达式由多个原语组成：
```markdown
原语(primitives)：由名称或数字，以及描述它的多个限定词组成。  
  * 限定词(qualifiers)
    * Types：设置数字或者名称所指示类型，例如host www.baidu.com，如果没有指定此值，则默认使用“host”关键字
        * host、post
        * net，设定子网， net 192.168.0.0 mask 255.255.255.0等价于net 192.168.0.0/24
        * port，设置端口范围，例如port 6000-8000
    * Dir：设置网络出入方向，例如dst port 80，如果没有特别指明来源或目的地，则默认使用“src or dst”作为关键字
        * src、dst、src or dst、src and dst(src：源端口，dst：目标端口)
    * Proto：指定协议类型，例如udp，如果没有特别指明是什么协议，则默认使用所有支持的协议
        * ether、fddi、tr、wlan、ip、ip6、arp、rarp、decnet、tcp、udp、icmp、igmp、icmp、igrp、pim、ah、esp、vrrp
    * 其他
        * gateway：指明网关IP地址，等价于ether host 'ehost' and not host 'host'
        * broadcast：广播报文，例如ether broadcast或者ip broadcast
        * multicast：多播报文，例如ip multicast或者ip6 multicast
        * less、greater：小于或者大于
  * 原语运算符
    * 与：&&或者and
    * 或：||或者or
    * 非：!或者not
```
<div style="color:orange; border-bottom: 1px solid #d9d9d9; 
	display: inline-block; 
	color: #999; 
	padding: 2px;">转载自：https://juejin.cn/post/6844904066229747720 </div> 

##### 应用示例
只抓取源端口或者目的端口范围6000到8000，并且是一个tcp协议或者ipv6的数据包
```
src or dst port 6000-8000 && tcp or ip6    
```
只抓取IP地址为192.168.0.10的数据包
```
host 192.168.0.10
```
#### 显示过滤器 
> **显示过滤器表达式作用在在Wireshark捕获数据包之后，从已捕获的所有数据包中显示出符合条件的数据包**

显示过滤表达式在工具栏下方的“应用显示过滤器”输入框输入即可生效
![1](https://bu.dusays.com/2022/11/12/636f11a82564a.png)
##### 基本过滤表达式
1. 一条基本的表达式由**过滤项**、**过滤关系**、**过滤值**三项组成  
2. 例如：`ip.addr == 192.168.1.1`，其中 `ip.addr` 为过滤项，`==` 为过滤关系，`192.168.1.1` 为过滤值。  
3. 该表达式的意思是 **找出所有ip协议中源或目标ip等于192.168.1.1的数据包**
###### 过滤项
1. Wireshark的过滤项是 `协议.协议字段` 的模式，Wireshark支持的全部协议及协议字段可查看[官方说明](https://www.wireshark.org/docs/dfref/)。
2. 以端口为例，端口出现于tcp协议中。所以有端口这个过滤项且其写法就是tcp.port  
3. Wireshark出于缩减长度的原因，有些字段没有使用协议规定的名称而是使用简写，比如Destination Port在Wireshark中写为dstport
4. Wireshark出于简便使用的原因，增加了一些协议中没有的字段，比如tcp协议只有源端口和目标端口字段，为了简便使用Wireshark增加了tcp.port来同时代表这两个字段
5. 实际使用时我们输入`协议.`后Wireshark就会有支持的字段提示
###### 过滤关系
过滤关系指的是大于、等于、小于等等式关系，具体可以看[官方给出的表](https://www.wireshark.org/docs/wsug_html/#DispCompOps)
![1](https://bu.dusays.com/2022/11/12/636f11ecb35db.png)
###### 过滤值
过滤值就是设定的过滤项应该满足过滤关系的标准，比如500、5000、50000等等。  
过滤值的写法一般已经被过滤项和过滤关系设定好了，只是填下自己的期望值就可以了。
##### 复合过滤表达式
所谓复合过滤表达示，就是指由多条基本过滤表达式组合而成的表达示。  
基本过滤表达式的写法还是不变的，复合过滤表达示多出来的东西就只是基本过滤表达示的“连接词”，我们依然直接参照[官方给出的表](https://www.wireshark.org/docs/wsug_html/#FiltLogOps)
![1](https://bu.dusays.com/2022/11/12/636f11cc4be71.png)
##### 常见显示过滤需求及其对应表达式
###### 数据链路层

```
筛选mac地址为04:f9:38:ad:13:26的数据包----eth.src == 04:f9:38:ad:13:26

筛选源mac地址为04:f9:38:ad:13:26的数据包----eth.src == 04:f9:38:ad:13:26
```

###### 网络层

```
筛选ip地址为192.168.1.1的数据包----ip.addr == 192.168.1.1

筛选192.168.1.0网段的数据---- ip contains "192.168.1"

筛选192.168.1.1和192.168.1.2之间的数据包----ip.addr == 192.168.1.1 && ip.addr == 192.168.1.2

筛选从192.168.1.1到192.168.1.2的数据包----ip.src == 192.168.1.1 && ip.dst == 192.168.1.2
```
###### 传输层

```
筛选tcp协议的数据包----tcp

筛选除tcp协议以外的数据包----!tcp

筛选端口为80的数据包----tcp.port == 80

筛选12345端口和80端口之间的数据包----tcp.port == 12345 && tcp.port == 80

筛选从12345端口到80端口的数据包----tcp.srcport == 12345 && tcp.dstport == 80
```

###### 应用层

```
特别说明----http中http.request表示请求头中的第一行（如GET index.jsp HTTP/1.1），http.response表示响应头中的第一行（如HTTP/1.1 200 OK），其他头部都用http.header_name形式。

筛选url中包含.php的http数据包----http.request.uri contains ".php"

筛选内容包含username的http数据包----http contains "username"
```
## 通过实验阐述ARP的工作原理
> **ARP即地址解析协议（Address Resolution Protocol），是根据IP地址获取MAC地址的一个TCP/IP协议**
> 
> **ARP用于解决同一个局域网上的主机或路由器的IP地址和MAC地址的映射问题**
> 
> **每一台主机都设有一个 ARP高速缓存，里面存有 本局域网上 各主机和路由器的IP地址到MAC地址的映射表**
### ARP工作流程
1. 当主机A要向**本局域网**上的某台主机B发送IP数据报时，就现在其ARP高速缓存中查找有无主机B的IP地址。若有，查出其对应的MAC地址，写入MAC帧；若没有，进行下述步骤
2. 主机A的ARP进程在本局域网上广播一个ARP请求分组，其中有自己的IP地址到MAC地址的映射
3. 本局域网上的所有主机运行的ARP进程都收到此ARP请求分组
4. 主机B的IP地址与ARP请求分组中要查询的IP地址一致，就收下这个ARP请求分组，将主机A的MAC映射写入自己的ARP高速缓存，并向主机A发送ARP响应分组，同时在这个ARP响应分组中写入自己的MAC地址。由于其余所有主机的IP地址都与ARP请求分组中要查询的IP地址不一致，因此不理睬
5. 主机A收到主机B的ARP响应分组后，就在其ARP高速缓存中写入主机B的IP地址到MAC地址的映射
### 实验步骤及内容
> **主机A**
> 
> 	**IP地址：192.168.31.248**
> 	
> 	**MAC地址：c0:3c:59:5e:37:47**
> 	
> **主机B**
> 
> 	**IP地址：192.168.31.186**
> 	
> 	**MAC地址：28:7f:cf:12:af:89**
#### ARP命令练习
1. 在`cmd`中使用`ipconfig/all`命令，查看自己的IP地址和MAC地址，同时让小组成员连接同一个`WIFI`执行相同的操作并记录
<center> 
	<img style="border-radius: 0.3125em; box-shadow: 0 2px 4px 0 rgba(34,36,38,.12),0 2px 10px 0 rgba(34,36,38,.08);" src="https://bu.dusays.com/2022/11/12/636f62756d2e9.png">
	<br>
	<div style="color:orange; border-bottom: 1px solid #d9d9d9; 
	display: inline-block; 
	color: #999; 
	padding: 2px;">主机A IP地址和MAC地址</div> 
 </center>
<center> 
	<img style="border-radius: 0.3125em; box-shadow: 0 2px 4px 0 rgba(34,36,38,.12),0 2px 10px 0 rgba(34,36,38,.08);" src="https://bu.dusays.com/2022/11/12/636f6331a7d39.png">
	<br>
	<div style="color:orange; border-bottom: 1px solid #d9d9d9; 
	display: inline-block; 
	color: #999; 
	padding: 2px;">主机B IP地址和MAC地址</div> 
 </center>


2. 主机A使用`arp -a`查看ARP缓存表
![1](https://bu.dusays.com/2022/11/12/636f603bde062.png)
3. 主机A通过`ping`主机B的IP来添加动态ARP缓存表数据
![2](https://bu.dusays.com/2022/11/12/636f60cfe4604.png)
我在`ping`主机B`ip`地址时碰到**请求超时**的问题。  
经排查，是因为windows防火墙默认设置的是不让别人ping通，通过修改防火墙相关设置解决了该问题。  
**步骤：控制面板 →  系统和安全 → Windows防火墙 → 高级设置 → 入站规则 → 文件和打印机共享（回显请求 - ICMPv4-In）设置为启用**
4. 主机A使用`arp -a`查看ARP缓存表，发生新增一条数据
![3](https://bu.dusays.com/2022/11/12/636f6169b6f50.png)
5. 以管理员身份运行`cmd`，执行`arp -d *`，删除缓存信息
![4](https://bu.dusays.com/2022/11/12/636f62661400d.png)

#### 抓包分析ARP协议
##### 当ARP缓存对应数据为空时
###### 实验步骤
1. 主机A执行`arp -d *`，删除缓存信息
2. 主机A运行Wireshark，设置显示过滤器表达式为`arp.dst.proto_ipv4 == 192.168.31.186 and arp.src.proto_ipv4 == 192.168.31.248 or icmp `
3. 主机A`ping`主机B的`ip地址`
###### 结果分析
1. 主机A将自己的`ip地址 192.168.31.248` & `MAC地址 c0:3c:59:5e:37:47`写入请求分组，并将`目的ip地址`设置为`192.168.31.186`，`目的MAC地址`设置为`00:00:00:00:00:00`，对本局域网内的所有主机进行广播
<center> 
	<img style="border-radius: 0.3125em; box-shadow: 0 2px 4px 0 rgba(34,36,38,.12),0 2px 10px 0 rgba(34,36,38,.08);" src="https://bu.dusays.com/2022/11/12/636f8f33f1a20.png">
	<br>
	<div style="color:orange; border-bottom: 1px solid #d9d9d9; 
	display: inline-block; 
	color: #999; 
	padding: 2px;">主机A发出的ARP请求分组</div> 
 </center>

2. 主机B收下这个ARP请求分组，将主机A的MAC映射写入自己的ARP高速缓存，并向主机A发送ARP响应分组，同时在这个ARP响应分组中写入自己的MAC地址，即`28:7f:cf:12:af:89`
3. 主机A收到主机B的ARP响应分组后，就在其ARP高速缓存中写入主机B的IP地址到MAC地址的映射
<center> 
	<img style="border-radius: 0.3125em; box-shadow: 0 2px 4px 0 rgba(34,36,38,.12),0 2px 10px 0 rgba(34,36,38,.08);" src="https://bu.dusays.com/2022/11/12/636f8e7d3f758.png">
	<br>
	<div style="color:orange; border-bottom: 1px solid #d9d9d9; 
	display: inline-block; 
	color: #999; 
	padding: 2px;">主机A收到的来自主机B的ARP响应分组</div> 
 </center>

<center> 
	<img style="border-radius: 0.3125em; box-shadow: 0 2px 4px 0 rgba(34,36,38,.12),0 2px 10px 0 rgba(34,36,38,.08);" src="https://bu.dusays.com/2022/11/12/636f8ea2d8434.png">
	<br>
	<div style="color:orange; border-bottom: 1px solid #d9d9d9; 
	display: inline-block; 
	color: #999; 
	padding: 2px;">主机A的ARP高速缓存表</div> 
 </center>

##### 当ARP缓存对应数据不为空时
###### 实验步骤
1. 主机A运行Wireshark，设置显示过滤器表达式为`arp.dst.proto_ipv4 == 192.168.31.186 and arp.src.proto_ipv4 == 192.168.31.248 or icmp`
2. 主机A `ping`主机B的`ip地址`
###### 结果分析
主机A没有发出`ARP`请求，而主机B接受到了主机A的ICMP报文，说明主机A直接使用了高速缓存区内的对应数据，而没有发出广播
<center> 
	<img style="border-radius: 0.3125em; box-shadow: 0 2px 4px 0 rgba(34,36,38,.12),0 2px 10px 0 rgba(34,36,38,.08);" src="https://bu.dusays.com/2022/11/12/636f910b7f31d.png">
	<br>
	<div style="color:orange; border-bottom: 1px solid #d9d9d9; 
	display: inline-block; 
	color: #999; 
	padding: 2px;">主机A发出的报文</div> 
 </center>

## 利用实验结果分析ICMP协议的报文结构字段定义
> **ICMP即互联网控制报文协议（Internet Control Message Protocol），网络设备（包括路由器）使用它来发送错误消息和指示与另一个IP 地址通信时成功或失败的操作信息**
<center> 
	<img style="border-radius: 0.3125em; box-shadow: 0 2px 4px 0 rgba(34,36,38,.12),0 2px 10px 0 rgba(34,36,38,.08);" src="https://bu.dusays.com/2022/11/12/636fbbc74f13c.png">
	<br>
	<div style="color:orange; border-bottom: 1px solid #d9d9d9; 
	display: inline-block; 
	color: #999; 
	padding: 2px;">ICMP报文结构</div> 
 </center>

### ICMP报文格式
```
+0------7-------15---------------31
|  Type | Code  |    Checksum    |
+--------------------------------+
|          Message Body          |
|        (Variable length)       |
+--------------------------------+
```
### ICMP报文格式解释
1. <u>Type</u>：占一个字节，标识ICMP报文的类型，可以分为差错报告报文和询问报文两大类
2. <u>Code</u>：占一个字节，用于进一步区分某种类型中的不同情况
3. <u>Checksum</u>：占两个字节，检验报文在传输过程中是否出现差错
### ICMP应用举例
#### Ping命令
> **「ping」是用来探测本机与网络中另一主机之间是否可达的命令**

在此次实验中，使用主机A在`cmd`环境下`ping baidu.com`，分析回送请求报文和回送回答报文
##### 回送请求报文
![1](https://bu.dusays.com/2022/11/13/63702d8239c61.png)
```
Internet Control Message Protocol
    Type: 8 (Echo (ping) request)
    Code: 0
    Checksum: 0x4ae9 [correct]
    [Checksum Status: Good]
    Identifier (BE): 1 (0x0001)
    Identifier (LE): 256 (0x0100)
    Sequence Number (BE): 626 (0x0272)
    Sequence Number (LE): 29186 (0x7202)
    [Response frame: 215]
    Data (32 bytes)
        Data: 6162636465666768696a6b6c6d6e6f7071727374757677616263646566676869
        [Length: 32]
```
1. Type的值为 **8**，Code的值为 **0**，表示回显请求
2. Checksum的值为 **0x4ae9**，这里校验和验证正确
3. <u>Identifier</u>：识别码，用于区分不同进程的应用。由于Window系统与Linux系统发出的ping报文的字节序不一样，所以需要 **BE** 和 **LE** 两个值，而这两个值所表示的十六进制值（HEX）是相同的。这里的 **BE** 指的是大端字节序，在Linux中使用；**LE**指的是小端字节序，在Windows中使用
4. <u>Sequence Number</u>：序列号，用于对应请求与响应。这里对于 **BE** 和 **LE** 解释同上。 
##### 回送回答报文
![2](https://bu.dusays.com/2022/11/13/63702d83032ff.png)
```
Internet Control Message Protocol
    Type: 0 (Echo (ping) reply)
    Code: 0
    Checksum: 0x52e9 [correct]
    [Checksum Status: Good]
    Identifier (BE): 1 (0x0001)
    Identifier (LE): 256 (0x0100)
    Sequence Number (BE): 626 (0x0272)
    Sequence Number (LE): 29186 (0x7202)
    [Request frame: 213]
    [Response time: 20.855 ms]
    Data (32 bytes)
        Data: 6162636465666768696a6b6c6d6e6f7071727374757677616263646566676869
        [Length: 32]
```
1. Type的值为 **0**，Code的值为 **0**，表示回送回答
2. Checksum的值为 **0x52e9**，这里校验和验证正确
3. <u>Identifier</u>：识别码，用于区分不同进程的应用
4. <u>Sequence Number</u>：序列号，用于对应请求与响应。这里的值 **626** 同上文 **回送请求报文** `Sequence Number` 的值，说明这俩请求和响应是对应的
#### Tracert命令
> **「Tracert」是用来显示可能的路由（路径）和测量数据包在 IP 网络中的传输延迟的命令**

在此次实验中，使用主机A在`cmd`环境下`tracert baidu.com`，分析报文

![1](https://bu.dusays.com/2022/11/13/63703bc9a2bf1.png)
##### 差错报告报文
ICMP的差错报告报文中，会把收到的需要进行差错报告的IP的数据提取出来作为ICMP报文的数据部分

![2](https://bu.dusays.com/2022/11/13/63703c4b4a1e1.png)
```
Internet Protocol Version 4, Src: 192.168.31.248, Dst: 110.242.68.66
    0100 .... = Version: 4
    .... 0101 = Header Length: 20 bytes (5)
    Differentiated Services Field: 0x00 (DSCP: CS0, ECN: Not-ECT)
        0000 00.. = Differentiated Services Codepoint: Default (0)
        .... ..00 = Explicit Congestion Notification: Not ECN-Capable Transport (0)
    Total Length: 92
    Identification: 0x1f2e (7982)
    000. .... = Flags: 0x0
        0... .... = Reserved bit: Not set
        .0.. .... = Don't fragment: Not set
        ..0. .... = More fragments: Not set
    ...0 0000 0000 0000 = Fragment Offset: 0
    Time to Live: 1
        [Expert Info (Note/Sequence): "Time To Live" only 1]
            ["Time To Live" only 1]
            [Severity level: Note]
            [Group: Sequence]
    Protocol: ICMP (1)
    Header Checksum: 0x0000 [validation disabled]
    [Header checksum status: Unverified]
    Source Address: 192.168.31.248
    Destination Address: 110.242.68.66

Internet Control Message Protocol
    Type: 8 (Echo (ping) request)
    Code: 0
    Checksum: 0xf4e4 [correct]
    [Checksum Status: Good]
    Identifier (BE): 1 (0x0001)
    Identifier (LE): 256 (0x0100)
    Sequence Number (BE): 794 (0x031a)
    Sequence Number (LE): 6659 (0x1a03)
    [No response seen]
        [Expert Info (Warning/Sequence): No response seen to ICMP request]
            [No response seen to ICMP request]
            [Severity level: Warning]
            [Group: Sequence]
    Data (64 bytes)
        Data: 000000000000000000000000000000000000000000000000000000000000000000000000…
        [Length: 64]
```
![3](https://bu.dusays.com/2022/11/13/63703c4c1fe7e.png)
```
Internet Control Message Protocol
    Type: 11 (Time-to-live exceeded)
    Code: 0 (Time to live exceeded in transit)
    Checksum: 0xf4ff [correct]
    [Checksum Status: Good]
    Unused: 00000000
    Internet Protocol Version 4, Src: 192.168.31.248, Dst: 110.242.68.66
        0100 .... = Version: 4
        .... 0101 = Header Length: 20 bytes (5)
        Differentiated Services Field: 0x00 (DSCP: CS0, ECN: Not-ECT)
            0000 00.. = Differentiated Services Codepoint: Default (0)
            .... ..00 = Explicit Congestion Notification: Not ECN-Capable Transport (0)
        Total Length: 92
        Identification: 0x1f2e (7982)
        000. .... = Flags: 0x0
            0... .... = Reserved bit: Not set
            .0.. .... = Don't fragment: Not set
            ..0. .... = More fragments: Not set
        ...0 0000 0000 0000 = Fragment Offset: 0
        Time to Live: 1
            [Expert Info (Note/Sequence): "Time To Live" only 1]
                ["Time To Live" only 1]
                [Severity level: Note]
                [Group: Sequence]
        Protocol: ICMP (1)
        Header Checksum: 0x069f [validation disabled]
        [Header checksum status: Unverified]
        Source Address: 192.168.31.248
        Destination Address: 110.242.68.66
    Internet Control Message Protocol
        Type: 8 (Echo (ping) request)
        Code: 0
        Checksum: 0xf4e4 [unverified] [in ICMP error packet]
        [Checksum Status: Unverified]
        Identifier (BE): 1 (0x0001)
        Identifier (LE): 256 (0x0100)
        Sequence Number (BE): 794 (0x031a)
        Sequence Number (LE): 6659 (0x1a03)
        Data (64 bytes)
            Data: 000000000000000000000000000000000000000000000000000000000000000000000000…
            [Length: 64]
```
1. Type的值为 **11**，Code的值为 **0**，表示超时报错
2. 图1的**回送请求报文**出错，图2相对应的**差错报告报文**，把图1报文的IP数据报的首部和数据字段的前8个字节提取出来，作为ICMP报文的数据字段
## 基于实验数据深入分析TCP协议功能
> **TCP即传输控制协议（Transmission Control Protocol），是面向连接的运输层协议**
### TCP报文格式 
![1](https://bu.dusays.com/2022/11/13/63704be4d65f3.png)
### TCP报文格式解释
1. <u>源端口</u>和<u>目的端口</u>：各占 2 字节，和 IP 头部的 **源地址** 和 **目的地址** 一起唯一地标识了每个连接
2. <u>序列号</u>：占 4 字节，TCP连接中传送的数据流中的**每一个字节都按顺序编号**，序号字段的值指的是**本报文段**所发送的数据的第一个字节的序号
3. <u>确认号</u>：占 4 字节，是期望收到对方的下一个报文段的数据的第一个字节的序号
4. <u>数据偏移</u>：占 4 位，它指出TCP报文段的数据起始处距离TCP报文段的起始处有多远，实际是指出TCP报文段的首部长度
5. <u>保留</u>：占 6 位，保留为今后使用，默认置0
6. <u>紧急 URG(URGent)</u>：当 URG = 1 时，表明紧急指针字段有效。它告诉系统此报文段中有紧急数据，应尽快传送(相当于高优先级的数据)
7. <u>确认 ACK(ACKnowledegment)</u>：只有当 ACK = 1 时确认号字段有效，当 ACK = 0 时确认号无效
8. <u>推送 PSH(PuSH)</u>：接收 TCP 收到 PSH = 1 的报文段，就尽快地交付接收应用进程，不再等到整个缓存都填满了后再向上交付 
9. <u>复位 RST(ReSeT)</u>：当 RST = 1 时，表明 TCP 连接中出现严重差错（如由于主机崩溃或其他原因）必须释放连接，然后再重新建立运输连接。RST置1还用来拒绝一个非法报文或拒绝打开一个连接
10. <u>同步 SYN(SYNchronization)</u>：在连接建立时用来同步序号。当 SYN = 1 而 ACK = 0 时，表明这是一个连接请求报文段。对方若同意建立连接，则在响应的报文段中使 SYN = 1 和 ACK = 1
11. <u>终止 FIN(FINish)</u>：用来释放一个连接。FIN = 1 表明此报文段的发送端的数据已发送完毕，并要求释放运输连接。
12. <u>窗口</u>：占 2 字节，指的是发送本报文段的一方的**接收窗口**。用于流量控制，指示接收方愿意接收的字节数量
13. <u>检验和</u>：占 2 字节，检验和字段检验的范围包括TCP首部和数据这两部分。在计算检验和时，要在 TCP 报文段的前面加上 12 字节的伪首部
14. <u>选项</u>：长度可变，最长可达 40 字节。如 **最长报文段长度MSS**、**窗口扩大**选项、**时间戳**选项等等
15. <u>填充字段</u>：仅仅是为了使整个TCP首部长度为 4 字节的整数倍
### 实验步骤 
1. 下载 [TCP/UDP Socket 调试工具](https://files.cnblogs.com/files/ggll611928/TCP-UDP-Socket%E8%B0%83%E8%AF%95%E5%B7%A5%E5%85%B7-v2.2.rar)
![1](https://bu.dusays.com/2022/11/13/6370874b20e3e.png)
2. 在`cmd`中`ping zhihu.com`，得到`ip地址`为`103.41.167.234`
![2](https://bu.dusays.com/2022/11/13/637087b2b3a4b.png)
3. 使用TCP调试工具，创建一个连接
![3](https://bu.dusays.com/2022/11/13/6370887550c8b.png)
4. 打开Wireshark，设置显示过滤器为 `ip.addr == 103.41.167.234`
![4](https://bu.dusays.com/2022/11/13/637088cda466f.png)
5. 在TCP调试工具中，点击 **连接**
![5](https://bu.dusays.com/2022/11/13/63708928070a7.png)
6. 在TCP调试工具中，发送数据 `Hello World!!!`后，连接自动断开
![6](https://bu.dusays.com/2022/11/13/63708c752ff6b.png)
7. 在Wireshark中捕获到以下数据包
![7](https://bu.dusays.com/2022/11/13/63708cca0d6f9.png)
### 三次握手
> **三次握手目的是保证双方都有发送和接收的能力**

![1](https://bu.dusays.com/2022/11/13/637052e140268.png)
- 一开始，客户端和服务端都处于 `CLOSE` 状态。先是服务端主动监听某个端口，处于 `LISTEN` 状态
- 客户端随机初始化 **序列号 seq** 为 **x**，同时把 **SYN** 置1，接着把报文发送给服务端。之后，TCP客户端进入 `SYN-SENT` 状态
![1](https://bu.dusays.com/2022/11/13/637090318e9b1.png)
- 服务器收到连接请求报文段后，若同意连接，将进行下述操作。首先，随机初始化自己的 **序列号 seq** 为 **y**，其次把 **确认号 ack** 置为 **x + 1**，接着 **SYN** 和 **ACK** 均置为1，最后把该报文发给客户端。这时，服务端进入`SYN-RCVD` 状态
![2](https://bu.dusays.com/2022/11/13/6370903f2af73.png)
- 客户端收到服务端报文后，还要向服务端回应最后一个应答报文。首先将应答报文的 **ACK** 置为1，**确认号 ack** 置为 **y + 1**，**序列号 seq** 置为 **x + 1**，最后把报文发送给服务端。之后，客户端处于`ESTABLISHED` 状态，因为它一收一发了
![3](https://bu.dusays.com/2022/11/13/63709042a0303.png)
- 服务端收到客户端的应答报文后，也进入 `ESTABLISHED` 状态，因为它也一收一发了
### 四次挥手
![1](https://bu.dusays.com/2022/11/13/637055a33c4fe.png)
- 客户端打算关闭连接，此时会发送一个 TCP 首部 `FIN` 标志位被置为 `1` 的报文并指明自己当前的 **序列号 seq** 为 **u**，之后客户端进入 `FIN_WAIT_1` 状态
![1](https://bu.dusays.com/2022/11/13/637095cced990.png)
- 服务端收到该报文后，就向客户端发送 `ACK` 应答报文，指明自己当前的 **序列号 seq** 为 **v**， **确认号 ack** 为 **u + 1**，接着服务端进入 `CLOSE_WAIT` 状态
![2](https://bu.dusays.com/2022/11/13/637095cf921e9.png)
- 客户端收到服务端的 `ACK` 应答报文后，之后进入 `FIN_WAIT_2` 状态
- 等待服务端处理完数据后，也向客户端发送 `FIN` 报文，报文的 `ACK` 置为 `1`，**序列号 seq** 为 **w**， **确认号 ack** 为 **u + 1**，之后服务端进入 `LAST_ACK` 状态
![3](https://bu.dusays.com/2022/11/13/637095d1574be.png)
- 客户端收到服务端的 `FIN` 报文后，回一个 `ACK` 应答报文，其中 **序列号 seq** 为 **u + 1**， **确认号 ack** 为 **w + 1**，之后进入 `TIME_WAIT` 状态
![4](https://bu.dusays.com/2022/11/13/637095d2df5ff.png)
- 服务端收到了 `ACK` 应答报文后，就进入了 `CLOSE` 状态，至此服务端已经完成连接的关闭
- 客户端在经过 `2MSL` 一段时间后，自动进入 `CLOSE` 状态，至此客户端也完成连接的关闭
## 访问外网某服务器，分析从MAC层协议、IP协议、TCP协议一直到HTTP协议的过程
### 网络包的旅途
1. 用户输入网址
2. 浏览器解析网址，生成 HTTP 消息
3. 在发送 HTTP 消息给 Web 服务器之前，浏览器先向 DNS 服务器发送请求，查询与服务器域名相对应的 IP 地址
4. 通过 DNS 获取到 IP 后，浏览器把 HTTP 消息转交给 Socket 库
5. Socket 库将收到的 HTTP 消息作为数据转交给协议栈
6. TCP 按照网络包的长度对数据进行拆分，在每个包前面加上 TCP 头部并转交给 IP
7. IP 在 TCP 包前面加上 IP 头部（目的 IP 为 Web 服务器 IP 地址，源 IP 为主机 IP 地址），IP 包生成后参考路由控制表决定接受此 IP 包的路由或主机的 IP 地址。随后，IP 包将被发送给连接这些路由器或主机网络接口的驱动程序
8. 如果尚不知道下一跳接收端的 MAC 地址，可以利用 ARP 查找，加上 MAC 头部，然后将包转交给网卡驱动
9. 网卡驱动收到 IP 模块发来的包，将其转交给网卡并发出发送指令
10. 网卡检查以太网的可发送状态，将数字信息转换为电信号发送出去
11. 服务端的局域网中有防火墙，对进入的包进行检查，判断是否允许通过
12. Web 服务器前面有如果有缓存服务器，会拦截通过防火墙的包如果用户请求的页面已经缓存在服务器上，则代替服务器向用户返回页面数据
13. 如果请求的页面没有被缓存，缓存服务器会将请求转发给 Web 服务器
14. Web 服务器收到包后，网卡和网卡驱动会接收这个包并转交给协议栈
15. 协议栈依次检查 IP 头部和 TCP 头部，如果没有问题则取出 HTTP 的数据块并进行组装
16. HTTP 消息恢复成原始状态，然后通过 Socket 库转交给 Web 服务器
17. Web 服务器分析 HTTP 消息的内容，并根据请求内容将读取的数据返回给客户端
18. 浏览器接收到响应包后，进行页面的渲染
19. HTTP请求结束，TCP连接断开
![1](https://bu.dusays.com/2022/11/15/6372e99613b66.jpg)
### DNS
#### DNS报文结构
![1](https://bu.dusays.com/2022/11/13/6370b7a2baa6b.png)
#### DNS查询步骤
浏览器在解析域名时，会经过下列步骤：
1. 浏览器会先看自身有没有对这个域名的缓存，如果有，就直接返回；如果没有，就去问操作系统
2. 操作系统也会去看自己的缓存，如果有，就直接返回；如果没有，再去 Hosts 文件看
3. 本地的 Hosts 文件，若有域名和 IP 地址的对应关系，直接使用该 IP 地址通信；如果没有，浏览器向本地域名服务器发出一个查询请求
4. 本地域名服务器查看有无缓存记录。若有，直接响应；若没有，本地域名服务器向根域名服务器查询
5. 根域名服务器响应本地域名服务器，给出对应域名的顶级域名服务器IP地址，让本地域名服务器去向其查询
6. 顶级域名服务器响应本地域名服务器，给出对应域名的权威域名服务器（权威 DNS 服务器，它是域名解析结果的原出处）IP地址，让本地域名服务器去向其查询
7. 权威 DNS 服务器查询后将对应的 IP 地址告诉本地 DNS 服务器
8. 本地 DNS 将 IP 地址返回给客户端，客户端和目标建立连接
### 实验步骤
1. 访问`http://www.smartclass.cn/Default.aspx`
2. 分析 `HTTP` 请求报文及 `HTTP` 响应报文
### 报文分析
![1](https://bu.dusays.com/2022/11/13/6370f2e0d407f.png)
#### HTTP报文结构
![1](https://bu.dusays.com/2022/11/13/6370f173089a1.png)
#### HTTP请求报文
##### 数据链路层
![1](https://bu.dusays.com/2022/11/13/6370f44ce10f8.png)
##### 网络层
![2](https://bu.dusays.com/2022/11/13/6370f585c0330.png)
##### 传输层
![3](https://bu.dusays.com/2022/11/13/6370f5871b2b2.png)
##### 应用层
![4](https://bu.dusays.com/2022/11/13/6370f670b78f0.png)
```
Hypertext Transfer Protocol
    GET /Default.aspx HTTP/1.1\r\n
    Host: www.smartclass.cn\r\n
    User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/107.0.0.0 Safari/537.36 Edg/107.0.1418.42\r\n
    Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9\r\n
    Accept-Encoding: gzip, deflate\r\n
    Accept-Language: zh-CN,zh;q=0.9,en;q=0.8,en-GB;q=0.7,en-US;q=0.6\r\n
    Upgrade-Insecure-Requests: 1\r\n
    \r\n
    [Full request URI: http://www.smartclass.cn/Default.aspx]
    [HTTP request 1/14]
    [Response in frame: 1787]
    [Next request in frame: 1804]
```
1. <u>请求行</u>：由 `请求方法字段`、`URL字段` 和 `HTTP协议版本字段` 组成，如 **GET /Default.aspx HTTP/1.1**
2. <u>请求头部</u>：关键字/值对组成，每行一对
	1. <u>Host</u>：请求的主机名
	2. <u>User-Agent</u>：发出请求的浏览器类型
	3. <u>Accept</u>：客户端可识别的内容类型列表
3. <u>空行</u>：最后一个请求头之后是一个空行，发送回车符和换行符，通知服务器以下不再有请求头
4. <u>请求数据</u>
#### HTTP响应报文
##### 传输层
- TCP 协议会分段传输过大的数据段（Segment）保证传输的性能
- TCP 协议引入了最大分段大小（Maximum segment size，MSS）这一概念，它是 TCP 数据段能够携带的数据上限。在正常情况下，TCP 连接的 MSS 是 MTU - 40 字节，即 1460 字节
	- MSS：一个网络包的最大长度，以太网中一般为 `1500` 字节
	- MTU：除去 IP 和 TCP 头部之后，一个网络包所能容纳的 TCP 数据的最大长度
- 该报文 MSS 值为 1360，数据段分成 8 份从服务端发出，并在客户端经过拼接后被接收
![1](https://bu.dusays.com/2022/11/13/6370fb4c09aa8.png)
##### 应用层
![1](https://bu.dusays.com/2022/11/13/6370fdbf7eb46.png)
```
Hypertext Transfer Protocol
    HTTP/1.1 200 OK\r\n
        [Expert Info (Chat/Sequence): HTTP/1.1 200 OK\r\n]
            [HTTP/1.1 200 OK\r\n]
            [Severity level: Chat]
            [Group: Sequence]
        Response Version: HTTP/1.1
        Status Code: 200
        [Status Code Description: OK]
        Response Phrase: OK
    Date: Sun, 13 Nov 2022 13:06:05 GMT\r\n
    Content-Type: text/html; charset=utf-8\r\n
    Content-Length: 9696\r\n
        [Content length: 9696]
    Connection: keep-alive\r\n
    Cache-Control: private\r\n
    Content-Encoding: gzip\r\n
    Vary: Accept-Encoding\r\n
    MANUFACTURER: Hanboer\r\n
    X-AspNet-Version: 4.0.30319\r\n
    X-UA-Compatible: IE=edge,chrome=1\r\n
    Access-Control-Allow-Headers: content-type\r\n
    Access-Control-Allow-Methods: GET,POST,PUT,DELETE,OPTIONS\r\n
    Access-Control-Allow-Origin: http://localhost:9527\r\n
    Access-Control-Allow-Credentials: true\r\n
    \r\n
    [HTTP response 1/14]
    [Time since request: 0.067102000 seconds]
    [Request in frame: 1776]
    [Next request in frame: 1804]
    [Next response in frame: 1806]
    [Request URI: http://www.smartclass.cn/Webapi/V1/Live/GetPublicLives?csrkToken=0aat6ee1aaks3&IsLiving=true&Sort=StartTime&Order=0&PageSize=8&PageNumber=1&attribute=]
    Content-encoded entity body (gzip): 9696 bytes -> 40818 bytes
    File Data: 40818 bytes
```
1. <u>状态行</u>：由 `HTTP版本` 、`状态码` 和`原因短语` 组成，如 **HTTP/1.1 200 OK**
2. <u>响应头部</u>：关键字/值对组成，每行一对
3. <u>空行</u>：最后一个响应头之后是一个空行，发送回车符和换行符，通知服务器以下不再有响应头
4. <u>响应正文</u>
## 参考
1. [Wireshark系列之4 捕获过滤器](https://blog.51cto.com/yttitan/1734425)
2. [网络——Wireshark工具](https://blog.51cto.com/u_13579643/3647795?articleABtest=0)
3. [WireShark的基本用法](https://juejin.cn/post/6844904066229747720)
4. [Wireshark使用教程（界面说明、捕获过滤器表达式、显示过滤器表达式）](https://www.cnblogs.com/lsdb/p/9254544.html)
5. [一文精讲Wireshark的抓包和分析](https://www.freebuf.com/sectool/256745.html)
6. [Wireshark简明教程，新手专用，挑实在的讲，不搞花里胡哨](https://bbs.huaweicloud.com/blogs/285673)
7. [WireShark网络封包抓包工具各个界面介绍](https://blog.51cto.com/u_15688254/5694733)
8. [实验3.利用Wireshark分析ARP协议](https://codeantenna.com/a/2zI6hbfTIM)
9. [如何计算IP或ICMP协议首部里的checksum字段](https://zhuanlan.zhihu.com/p/364195316)
10. [带你深入熟悉你所不知道的ICMP](https://blog.51cto.com/ccieh3c/2654283)
11. [使用Wireshark学习网络协议之ICMP](https://zhaoqqi.github.io/2016/10/05/network-wireshark-arp/)
12. [实战！我用 Wireshark 让你“看见“ TCP](https://www.cnblogs.com/xiaolincoding/p/12922927.html)
13. [4.1 TCP 三次握手与四次挥手面试题](https://xiaolincoding.com/network/3_tcp/tcp_interview.html)
14. [Wireshark抓包TCP三次握手](https://blog.51cto.com/u_15103025/2643297)
15. [TCP 中的三次握手和四次挥手](https://rgb-24bit.github.io/blog/2019/tcp-connect-manage.html)
16. [Wireshark配合TCP调试工具理解TCP三次握手和四次挥手过程](https://blog.csdn.net/u014117943/article/details/118520498)
17. [老生常谈的TCP三次握手和四次挥手，你会了吗？](https://juejin.cn/post/7034547558664011783)
18. [HTTP请求报文和HTTP响应报文](https://www.cnblogs.com/biyeymyhjob/archive/2012/07/28/2612910.html)
19. [为什么 TCP/IP 协议会拆分数据](https://draveness.me/whys-the-design-tcp-segment-ip-packet/)
20. [HTTP的曲折：网络请求到层层封装和终端拆分](https://www.pianshen.com/article/86011166321/)
21. [浅谈http协议（三）：HTTP 报文及其结构](https://segmentfault.com/a/1190000019788537)
22. [Wireshark官方文档](https://www.wireshark.org/docs/wsug_html_chunked/ChapterWork.html)


