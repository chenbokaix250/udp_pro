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
















