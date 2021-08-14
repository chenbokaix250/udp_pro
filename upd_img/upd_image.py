# -*- coding: utf-8 -*- 

import socket
import cv2 
import numpy as np 
import struct


s = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)

s.bind(('127.0.0.1',1111))

print('Bind UDP on 1111...')

print('开始监听')

while True:
	fhead_size = struct.calcsize('l')
	buf,addr = s.recvfrom(fhead_size)
	print('ok')
	if buf:
		data_size = struct.unpack('l',buf)[0]

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
	print('Reviced!')
	print(len(data_total))
	nparr = np.fromstring(data_total,np.uint8)
	img_decode = cv2.imdecode(nparr,cv2.IMREAD_COLOR)
	cv2.imshow('result',img_decode)
	cv2.waitKey(1500)
	cv2.imwrite('take_over.jpg',img_decode)
	reply = 'get message!!!'
	s.sendto(reply.encode('utf-8'),addr)
	break
cv2.destroyAllWindows()