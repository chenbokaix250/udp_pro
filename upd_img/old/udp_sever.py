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
	cv2.waitKey(500)
	reply = "get message!!!"
	s.sendto(reply.encode('utf-8'), addr)
	cv2.destroyAllWindows()