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
    for((i=1;i<4;i++));
    do
        echo "equip:发送message1"

        ./client_msg $value_address 3000 1 150 250 300 450 35.58 45.77 1 

        
        
        echo "equip:发送message2"

        ./client_msg $value_address 3030 1 150 250 300 450 35.58 45.77 1 
        
        

        echo "equip:发送image1"

        ./client_img $value_address 4000 ../image/a1.jpg 

    
    
        echo "equip:发送image2"

        ./client_img $value_address 4040 ../image/tst.jpg

        
        
        echo  "equip:完成发送"

 
    done

    ./server_cmd 2000

    value1=`./server_cmd 2000` 
fi



if [[ $value1 =~ "end" ]] 
then
    
    echo "equip:关闭光电设备。"

    pkill -f server_cmd
    #kill -9 $(ps -e | grep server_cmd | awk '{print $1}')
    exit 0
fi
