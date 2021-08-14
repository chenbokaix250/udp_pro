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