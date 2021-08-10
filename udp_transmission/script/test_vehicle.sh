#!/bin/bash
echo "车辆到达指定位置!"
cd ..
cd build
echo $(pwd)

pkill -f server_img
pkill  -f server_msg
pkill -f server_video
value1=`./client_cmd 127.0.0.1 2000 start`
value2=$?
value3=$1

#echo "value1:$value1"
#echo "value2:$value2"


if [[ $value1 =~ "success" ]] 
then 
    nohup ./server_msg 3000 > msg  2>&1 &
    nohup ./server_img  4000 > img 2>&1 &
    nohup ./server_msg 3030 > msg2  2>&1 &
    nohup ./server_img  4040 > img2 2>&1 &
    echo "监听程序就绪！"
    if [[ $value3 =~ "test"  ]]
    then
        nohup ./server_video 5000 > videog 2>&1 &
        echo "监听视频打开！"  
    fi
else 
    echo "光电设备尚未启动"
fi

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
    if [[  -e $msg_file1 ]]
    then
        echo "msg1传输完成！"
        msg1_get=1
    else
        ./client_cmd 127.0.0.1 2000 msg1 
        sleep 1s
    fi

    if [[  -e $msg_file2 ]]
    then
        echo "msg2传输完成！"
        msg2_get=1
    else
        ./client_cmd 127.0.0.1 2000 msg2
        sleep 1s
    fi

    if [[  -e $img_file1 ]]
    then
        echo "img1传输完成！"
        img1_get=1
    else
        ./client_cmd 127.0.0.1 2000 img1 
        sleep 1s
    fi

     if [[  -e $img_file2 ]]
    then
        echo "img2传输完成！"
        img2_get=1
    else
        ./client_cmd 127.0.0.1 2000 img2
        sleep 1s
    fi
    #echo $msg1_get
    #echo $msg2_get
    if [[  $msg1_get>0 ]] && [[  $msg2_get>0 ]] && [[  $img1_get>0 ]] && [[  $img1_get>0 ]]
    then
        echo  "传输全部完成！"
        
        break
    fi

    sleep 3s
done

sleep 5s
value4=`./client_cmd 127.0.0.1 2000 end`
if [[ $value4 =~ "shut down" ]] 
then
    echo "发送关闭指令！"
fi 