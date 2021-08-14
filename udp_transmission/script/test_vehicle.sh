#!/bin/bash
echo "车辆到达指定位置!"
cd ..
cd build
#echo $(pwd)
value_address="127.0.0.1"
pkill -f server_img
pkill  -f server_msg
pkill -f server_video
./client_cmd $value_address 2000 1000

nohup ./server_msg 3000 > msg  2>&1 &
nohup ./server_img  4000 > img 2>&1 &
nohup ./server_msg 3030 > msg2  2>&1 &
nohup ./server_img  4040 > img2 2>&1 &
echo "监听程序就绪！"

msg_file1="../message/msg3000.txt"
msg_file2="../message/msg3030.txt"

img_file1="../image/img4000.jpg"
img_file2="../image/img4040.jpg"

msg1_get=0
msg2_get=0
img1_get=0
img2_get=0

while((1))
do

    if [[ -e $msg_file1 ]]
    then
        #echo "msg1传输完成！"
        msg1_get=1
    fi

    if [[ -e $msg_file2 ]]
    then
        #echo "msg2传输完成！"
        msg2_get=1
    fi

    if [[ -e $img_file1 ]]
    then
        #echo "img1传输完成！"
        img1_get=1
    fi

    if [[ -e $img_file2 ]]
    then
        #echo "img2传输完成！"
        img2_get=1
    fi

    if [[  $msg1_get>0 ]] && [[  $msg2_get>0 ]] && [[  $img1_get>0 ]] && [[  $img1_get>0 ]]
    then
        echo  "传输全部完成！"
        
        break
    fi

done

sleep 5s
./client_cmd 127.0.0.1 2000 1100
echo "发送关闭指令！"