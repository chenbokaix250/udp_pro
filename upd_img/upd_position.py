# -*- coding: utf-8 -*- 

import socket
import cv2 
import numpy as np 
import struct
import json

s = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)

s.bind(('127.0.0.1',2222))

print('Bind UDP on 2222...')

print('开始监听')

while True:
	
	buf,addr = s.recvfrom(1024)
	position = json.loads(buf)
	print(position)
	s.close()
	break



if position[-1] == 9527:

	f = open("position.txt",'a')
	str = ' '.join('%s'%i for i in position)
	f.write(str)
	f.write('\n')