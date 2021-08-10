#!/bin/bash

value_address=192.168.1.101
cd ../build

echo "发送message1"

./client_msg $value_address 3000 1 150 250 300 450 35.58 45.77 1 

echo "发送message2"

./client_msg $value_address 3030 1 150 250 300 450 35.58 45.77 1 


echo "发送image1"

./client_img $value_address 4000 ../image/a1.jpg 

echo "发送image2"

./client_img $value_address 4040 ../image/tst.jpg

echo  "完成发送"