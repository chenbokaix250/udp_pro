#!/bin/bash
value_address="192.168.1.101"
cd ..
cd build

echo $(pwd)

value1=`./server_cmd 2000`

value2=$?

echo "value1:$value1"

if [[ $value1 =~ "start" ]] 
then
    echo "equip:发送message1"

    ./client_msg $value_address 3000 1 150 250 300 450 35.58 45.77 1 

    
    
    echo "equip:发送message2"

    ./client_msg $value_address 3030 1 150 250 300 450 35.58 45.77 1 
    
    

    echo "equip:发送image1"

    ./client_img $value_address 4000 ../image/a1.jpg 

   
   
    echo "equip:发送image2"

    ./client_img $value_address 4040 ../image/tst.jpg

    
    
    echo  "equip:完成发送"

     ./server_cmd 2000

    value1=`./server_cmd 2000`  


fi



if [[ $value1 =~ "msg1" ]]
then
    echo "equip:发送message1"

    ./client_msg $value_address 3000 1 150 250 300 450 35.58 45.77 1 
    
    ./server_cmd 2000

    value1=`./server_cmd 2000` 
fi 

if [[ $value1 =~ "msg2" ]]
then
    echo "equip:发送message2"

    ./client_msg $value_address 3030 1 150 250 300 450 35.58 45.77 1 
    
    ./server_cmd 2000

    value1=`./server_cmd 2000`
fi 

if [[ $value1 =~ "img1" ]]
then
    echo "equip:发送image1"

    ./client_img $value_address 4000 ../image/a1.jpg 
    
    ./server_cmd 2000 

    value1=`./server_cmd 2000`
fi 

if [[ $value1 =~ "img2" ]]
then
    echo "equip:发送image1"

    ./client_img  $value_address  4040 ../image/a1.jpg 
    
    ./server_cmd 2000 

    value1=`./server_cmd 2000`
fi 

if [[ $value1 =~ "end" ]] 
then
    
    echo "equip:关闭光电设备。"

    pkill -f server_cmd
    exit 0
fi


cd ../script

./equipment_router.sh 