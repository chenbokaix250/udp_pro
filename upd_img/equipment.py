#!/usr/bin/python3
# -*- coding: UTF-8 -*-

import time
import subprocess
import socket
import cv2 
import numpy as np
import struct

import json
#--------------侦查过程-----------------


print("发现隐蔽区标识物!")

time.sleep(1)

print("已经完成自主停车!")

time.sleep(1)

#subprocess.call("python3 upd_take_over.py",shell=True)


print("侦查开始!")

print("侦查过程中发现目标!")

print("udp发送目标图片! 通道在1111")

s = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)

img = cv2.imread('tst.jpg')

img_encode = cv2.imencode('.jpg',img)[1]
data_encode = np.array(img_encode)
data = data_encode.tostring()
print(len(data))

fhead = struct.pack('l',len(data))

# 发送文件头
s.sendto(fhead,('127.0.0.1',1111))
#循环发送图片码流
for i in range(len(data)//1024+1):
	if 1024*(i+1)>len(data):
		s.sendto(data[1024*i:], ('127.0.0.1', 1111))
	else:
		s.sendto(data[1024*i:1024*(i+1)], ('127.0.0.1', 1111))
# 接收应答数据:
print(s.recv(1024).decode('utf-8'))


potision = [435,1680,223,669,38.84824847972115, 105.74474173648426,9527]
json_string = json.dumps(potision)
json_string = json_string.encode('UTF-8')

s.sendto(json_string,('127.0.0.1',2222))

s.close()

