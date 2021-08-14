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
