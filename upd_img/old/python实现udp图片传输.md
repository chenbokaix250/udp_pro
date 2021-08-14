# python实现udp图片传输

首先要了解UDP的工作模式

![a.jpeg](https://i.loli.net/2021/07/17/RoI4NcZOVWsUGLF.jpg)

对于服务器，首先绑定IP和端口，本机测试的时候可以使用127.0.0.1是本机的专有IP，端口号 大于1024的是自定义的，所以用大于1024的端口号，然后接收客户端数据，处理，返回
 对于客户端，UDP不用建立连接，只管发送不管接收到没有，所以可以直接对服务器的IP地址和端口号发送信息，然后等待应答。

注意传输的数据是二进制流数据，所以要找方法把需要传输的数据编码成二进制码流，传过去之后再解码即可，这里我用到了opencv读取图片成numpy的array格式，然后编码，传输，最后接到之后再解码。

先说一次性传输整个图片，这个思路就是接受的参数设置很大，而且图片比较小的情况，实现比较简单

首先是服务器脚本，实现了接收、显示、应答

## udp_sever.py
```python
# -*- coding: utf-8 -*-


import socket
import cv2
import numpy as np

s = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)

s.bind(('127.0.0.1',9999))

print('Bind UDP on 9999...')

while True:
  data,addr = s.recvfrom(65535)
  print('Received from %s:%s.'%addr)

  nparr = np.fromstring(data,np.uint8)

  img_decode = cv2.imdecode(nparr,cv2.IMREAD_COLOR)
  cv2.imshow('result',img_decode)
  cv2.waitKey()
  reply = "get message!!!"
  s.sendto(reply.encode('utf-8'), addr)
  cv2.destroyAllWindows()
```
客户端脚本,实现了发送图片,接收应答

## udp_client.py
```python
# -*- coding: utf-8 -*-
import socket
import cv2
import numpy as np

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

img = cv2.imread('b.jpg')
img_encode = cv2.imencode('.jpg', img)[1]
data_encode = np.array(img_encode)
data = data_encode.tostring()

# 发送数据:
s.sendto(data, ('127.0.0.1', 9999))
# 接收数据:
print(s.recv(1024).decode('utf-8'))

s.close()
```

为了方便理解放一下图片转到二进制再转回图片的代码

```python
import numpy as np 
import cv2 

#img = cv2.imread('a.png')
img = cv2.imread('b.jpg')
img_encode = cv2.imencode('.jpg',img)[1]
data_encode = np.array(img_encode)
str_encode = data_encode.tobytes()
print(len(str_encode))

# a.png 813611
# b.jpg 62470

#nparr = np.fromstring(str_encode,np.uint8)
nparr = np.frombuffer(str_encode,np.uint8)
img_decode = cv2.imdecode(nparr,cv2.IMREAD_COLOR)
cv2.imshow('result',img_decode)
cv2.waitKey()
cv2.destroyAllWindows()
```

分批传输图片

搞了好久终于知道怎么分批传输图片了，首先要知道需要传的图片需要多长的内存，不然不知道什么时候停止接收，这样就要考虑加一个文件头，告诉服务器要接受多长的码流。

实现思路是，首先客户端要先发送一个文件头，包含了码流的长度，用一个long int型的数，先用struct.pack打包，发过去，然后循环发送图片的码流即可

接着服务器先接到文件头，确认图片码流的长度，然后循环接收确定长度的码流，最后再解码成图片即可

实现代码如下：

首先是客户端脚本

## udp_client.py
```python
# -*- coding: utf-8 -*-

import socket
import cv2 
import numpy as np
import struct 


s = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
img = cv2.imread('a.png')

img_encode = cv2.imencode('.png',img)[1]
data_encode = np.array(img_encode)
data = data_encode.tostring()
print(len(data))
#定义头文件,打包成结构体
fhead = struct.pack('l',len(data))

# 发送文件头
s.sendto(fhead,('127.0.0.1',9999))
#循环发送图片码流
for i in range(len(data)//1024+1):
  if 1024*(i+1)>len(data):
    s.sendto(data[1024*i:], ('127.0.0.1', 9999))
  else:
    s.sendto(data[1024*i:1024*(i+1)], ('127.0.0.1', 9999))
# 接收应答数据:
print(s.recv(1024).decode('utf-8'))
#关闭
s.close()
```
然后是服务器接收

## udp_sever.py
```python
# -*- coding: utf-8 -*-

import socket
import cv2
import numpy as np
import struct


s = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)

s.bind(('127.0.0.1',9999))

print('Bind UDP on 9999...')

while True:
  #print("ok")
  fhead_size = struct.calcsize('l')
  #fhead_size = 65535
  buf,addr = s.recvfrom(fhead_size)
  print(buf)
  #print(addr)
  if buf:
    data_size = struct.unpack('l',buf)[0]
    print(data_size)
    print("---")
  recvd_size = 0
  data_total = b''
  while not recvd_size == data_size:
    if data_size - recvd_size > 1024:
      data,addr = s.recvfrom(1024)
      #print(len(data))
      #print('!!!')
      recvd_size += len(data)
    else:
      data,addr = s.recvfrom(1024)
      recvd_size = data_size
    data_total +=data
  print('Reveived')
  nparr = np.fromstring(data_total,np.uint8)
  img_decode = cv2.imdecode(nparr,cv2.IMREAD_COLOR)
  cv2.imshow('result',img_decode)
  cv2.waitKey(500)
  reply = "get message!!!"
  s.sendto(reply.encode('utf-8'),addr)
  cv2.destroyAllWindows()

```

---

上面是基本的实现，经过一番学习我终于掌握了UDP传输的精髓

首先是确定客户端和服务器的运行机制

客户端：先定义一个socket对象，不用绑定，然后指定IP地址和端口发送消息，然后如果用了recvfrom就会一直阻塞等待应答（这个很有用，作用就是保证对方确实收到，再发新的消息，不用在考虑发送频率的问题了），前面加一个while True就可以循环发送了，如果涉及到很大的消息，可以拆分发送，技巧是先发送一个文件头高速服务器要发的内容有多大（文件头这里建议使用stuct库，看前面例程），然后随后发送文件内容，保证要循环发送，因为每次发送，对面就当发了一次，假如发了2048字节的内容，对面设置的每次收1024，那么剩下的1024就被丢掉了，而不是等待下次继续接收。还有就是发送的是二进制的码流，目前我用到的转换成码流的方法有：图片用opencv,先imencode 转成二进制，然后再转成numpy，然后再tostring。文件头这种，需要确切知道占多大内存，使得服务器好接收的，用了stuct库，里面的pack,unpack,calcsize三个函数非常好用，发送的时候把数据pack一下就能发送了。列表、字典等等，作为文件内容，用到了json，有点万能，先json.dumps转换成json类型，然后再encode编码成二进制即可拿去发送了。

服务器：先定义一个socket对象，绑定IP地址和端口，让客户端可以找到，然后等待接收消息，收到消息之后处理消息，应答，配合客户端的recvfrom，保证接收频率一致，服务器为了保证始终接收消息，一定会有一个while True,接收到的消息是二进制码流，因此要进行解码。针对上面讲的编码方式解码，其实就是编码方式的反向操作：图片，用opencv解码，先是np.fromstring，然后再cv2.imdecode(data, cv2.IMREAD_COLOR)。对于接收文件头，这里有点技巧，用struct.calcsize确定文件头长度，然后只接收这个长度的码流，再unpack出来即可，这里unpack是个元组。对于json，解码就是先decode,再json.loads即可，是上面编码的反向操作。

然后再高端一点的操作，同一个脚本多进程工作，这就要用到了threading.Thread创建多个进程，思路就是新建多个服务器，然后分配给不同的进程，他们的IP地址可以一样，端口号不一样就行，然后就可以在同一个脚本里并行工作了，这里不同于TCP，因为UDP不需要建立连接

然后附上我实现的源码，服务器脚本里有两个进程，一个接收客户端1的图片，另一个接收客户端2的列表

服务器

## udp_server.py
```python
# -*- coding: utf-8 -*-
import socket
import cv2
import numpy as np
import struct
import threading
import json

# 设置IP地址,两个服务器端口号
dest_ip = '127.0.0.1'
img_port = 9999
msg_port = 6666

# 服务器1的处理/应答函数/接收图片/显示/应答

def receive_img(rec_img):
  while True:
    # 接收数据
    fhead_size = struct.calcsize('l')
    buf,addr = rec_img.recvfrom(fhead_size)
    if buf:
      data_size = struct.unpack('l',buf)[0]
      print(data_size)
    recvd_size = 0
    data_total = b''
    while not recvd_size == data_size:
      if data_size - recvd_size > 1024:
        data,addr = rec_img.recvfrom(1024)
        recvd_size += len(data)
      else:
        data,addr = rec_img.recvfrom(1024)
        recvd_size = data_size
      data_total += data
    print('Received')
    nparr = np.fromstring(data_total,np.uint8)
    img_decode = cv2.imdecode(nparr,cv2.IMREAD_COLOR)
    cv2.imshow('result',img_decode)
    cv2.waitKey(100)
    reply = "get message!!!"
    rec_img.sendto(reply.encode('utf-8'),addr)
    cv2.destroyAllWindows()

def receive_msg(rec_msg):
  while True:
    msg_data,msg_addr = rec_msg.recvfrom(1024)
    msg_str = msg_data.decode('utf-8')
    msg = json.loads(msg_str)
    print(msg)
    reply = 'get the msg'
    rec_msg.sendto(reply.encode('utf-8'),msg_addr)
    rec_msg.close()

def main():
  rec_img = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
  rec_msg = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)

  rec_img.bind((dest_ip,img_port))
  rec_msg.bind((dest_ip,msg_port))

  t_recimg = threading.Thread(target=receive_img,args=(rec_img,))
  t_recmsg = threading.Thread(target=receive_msg,args=(rec_msg,))
  #开始进程
  t_recimg.start()
  t_recmsg.start()
  print('程序正常运行!!!')

if __name__== '__main__':
  main()

```

客户端

## udp_client_1.py
```python
#  -*- coding: utf-8 -*-
import socket
import cv2
import numpy as np
import struct

s = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
cap = cv2.VideoCapture(0)
#cap.set(3,320)
#cap.set(4,240)

while True:
  if cap.isOpened():
    flag,img = cap.read()
    img_encode = cv2.imencode('.jpg',img)[1]
    data_encode = np.array(img_encode)
    data = data_encode.tostring()
    
    fhead = struct.pack('l',len(data))
    s.sendto(fhead,('127.0.0.1',9999))

    for i in range(len(data)//1024+1):
      if 1024*(i+1)>len(data):
        s.sendto(data[1024*i:],('127.0.0.1',9999))
      else:
        s.sendto(data[1024*i:1024*(i+1)],('127.0.0.1',9999))
  cv2.waitKey(1)
  print(s.recv(1024).decode('utf-8'))

s.close()
```

## udp_client_2.py
```python
#  -*- coding: utf-8 -*-
import socket
import cv2
import numpy as np 
import struct
import json
import time 

send_msg = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
target_ip = '127.0.0.1'
target_port = 6666

while True:
  data = [0,0,0,1]
  data_str = json.dumps(data)
  send_msg.sendto(data_str.encode(),(target_ip,target_port))
  time.sleep(0.01)
  print(send_msg.recv(1024).decode('utf-8'))

```
以上就是本文的全部内容，希望对大家的学习有所帮助。

---

## UDP发送中的一个问题

试图通过UDP发送数据,但是显示错误:
`socket.error: [Errno 40] Message too long`

Mac实际上能发送的最大字长是9253字节.OSX将最大UDP包限制为9216字节.
可以使用终端中的命令进行更改:
`sudo sysctl -w net.inet.udp.maxdgram=65535`

更改后,则不会出现限制的错误问题

