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