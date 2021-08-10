# 项目中UDP沟通对接

## 项目背景

需要利用UDP发送检测信息，包括：检测框信息、目标位置信息、目标图像、目标属性。

测试时需要显示目标视频信息，方便双方联调。

## 通信架构图

![Communication architecture.png](https://i.loli.net/2021/08/03/aKqvZLzbIdg8wcj.png)

## Demo

### Require

`CMake and OpenCV`

### install 

```
git clone https://github.com/chenbokai/udp_transmission.git

cd udp_transmission/
`
cmake .&&make
```

### message

message command include two parts: client & server

client_msg parameters include(total10) : 

| List0  |List1 |List2 |List3 |List4 |List 5|List6 |List7 |List8 |List9 |
|----|----|----|----|----|----|----|----|----|----|
|State|server|Port|Xmin|Xmax|Ymin|Ymax|Xpos|Ypos|Flag|

State 表示当前设备所处的状态

server 表示传输地址

Port  表示传输端口号

检测框信息
（Xmin，Ymin）和（Xmax，Ymax） 表示检测框在图像上的坐标点 如下图所示

![Untitled Diagram.png](https://i.loli.net/2021/08/10/OLW6UGowqeaC9xm.png)

Xpos和Ypos是障碍物在侦察设备坐标系下的距离信息

![Untitled Diagram _1_.png](https://i.loli.net/2021/08/10/Ea6Zpbu2o8hHq4M.png)

State 0,1,2:
* 0 --- init
* 1 --- working
* 2 --- over

Flag 0, 1,2:
* 0 --- no detect
* 1 --- Lable1
* 2 --- Label 2

server_msg only has 1  parameters:
* Port

#### how to run
```
./server_msg 2000
./client_msg 127.0.0.1 2000 150 350 200 400 35.85 46.73 2
```
>推荐端口大于1024，0-1024端口被系统占用。

### image

image command include two parts:client& server

client_img has three parameters:
* Server
* Port 
* image Address

server_msg only has 1 parameters:
* Port

#### how to run

```
./server_img 2000
./client_img 127.0.0.1 2000 image/tst.jpg
```
>接收的图片会以taker_over+端口号的命名 保存在image文件夹中

### video
 
 video command imclude tow parts:client& server

 client_video has three parameters:
 * Server 
 * Port

 server_msg only has 1 parameters:
 * Port

 #### how to run

 ```
 ./server_video 2000
 ./client_video 127.0.0.1 2000 
 ```

---
8月4日 完成发送脚本设计工作


## 脚本架构

![Script_design.png](https://i.loli.net/2021/08/05/J3cln8bgmBfZPdT.png)

### script

>说明
`init_kill.sh`              用于初始化，删除过程文件
`kill_video`               用于测试模式时，结束video挂起进程
`send_sim.sh`         用于模拟msg和img的发送
`test_vehicle.sh`    接收自动化脚本，用于完成进程管理、文件确认、监听管理

#### how to run
```
./init_kill.sh #删除之前的过程文件
./test_vehicle.sh #启动监听   参数test可用与启动video（Port 5000）
./send_sim.sh  #启动发送模拟程序，发送msg1，msg2，img1，img2
./kill_video #启动利用test启动 test_vehicle时，video是挂起的，结束时需要关闭其进程
```

----

### 请求脚本设计

当网络阻塞 冲突导致接收任务未能完全完成时，需要进行请求来重启发送

所以对脚本进行了重新编写设计 根据返回的打印输入 重新完成接收 并校对接收的完整性

后因为脚本设计缺陷 导致异常退出 目前原因仍在排查

现利用重新发送3次，来避免网络阻塞
## Todo

~~后期加入 启动和结束的通信~~  已完成

~~进一步优化通信设计方案~~  已完成脚本优化设计

~~双向联调测试~~ 已完成

根据用户需求，做进一步改进

待测试后敲定相关协议


