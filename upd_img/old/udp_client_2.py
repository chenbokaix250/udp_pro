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

	
