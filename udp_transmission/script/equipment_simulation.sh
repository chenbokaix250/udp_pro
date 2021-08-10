#!/bin/bash

cd ..
cd build

echo $(pwd)

value1=`./server_cmd 2000`

value2=$?

echo "value1:$value1"

if [[ $value1 =~ "start" ]] 
then
    echo "发送message1"

    ./client_msg 127.0.0.1 3000 1 150 250 300 450 35.58 45.77 1 
    
    echo "发送message2"

    ./client_msg 127.0.0.1 3030 1 150 250 300 450 35.58 45.77 1 
    
    echo "发送image1"

    ./client_img 127.0.0.1 4000 ../image/a1.jpg 
   
    echo "发送image2"

    ./client_img 127.0.0.1 4040 ../image/tst.jpg
    
    echo  "完成发送"

    value1=`./server_cmd 2000`  
fi

if [[ $value1 =~ "msg1" ]]
then
    echo "发送message1"

    ./client_msg 127.0.0.1 3000 1 150 250 300 450 35.58 45.77 1 
    value1=`./server_cmd 2000`  
fi 

if [[ $value1 =~ "msg2" ]]
then
    echo "发送message2"

    ./client_msg 127.0.0.1 3030 1 150 250 300 450 35.58 45.77 1 
    value1=`./server_cmd 2000`  
fi 

if [[ $value1 =~ "img1" ]]
then
    echo "发送image1"

    ./client_img 127.0.0.1 4000 ../image/a1.jpg 
    value1=`./server_cmd 2000`  
fi 

if [[ $value1 =~ "img2" ]]
then
    echo "发送image1"

    ./client_img 127.0.0.1 4040 ../image/a1.jpg 
    value1=`./server_cmd 2000`  
fi 

if [[ $value1 =~ "end" ]] 
then
    sleep 2s
    echo "关闭光电设备。"
    exit 8
fi

./server_cmd 2000