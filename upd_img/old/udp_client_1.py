# -*- coding: utf-8 -*-
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