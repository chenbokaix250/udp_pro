#!/bin/bash
#value_address="192.168.1.101"
value_address="127.0.0.1"
cd ..
cd build

echo $(pwd)

value1=`./server_cmd 2000`

value2=$?

echo "value1:$value1"

if [[ $value1 =~ "1000" ]]
then
    for((i=1;i<4;i++));
    do
        echo "equip:发送message1"

        ./client_msg $value_address 6000 2 150 250 300 450 35.58 45.77 1

        
        


        
        
        echo  "equip:扫描完成"

 
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
