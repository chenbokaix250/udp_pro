#include "../lib/PracticalSocket.h"
#include <iostream>
#include <cstdlib>

#define BUF_LEN 65540

#include "opencv2/opencv.hpp"

using namespace cv;
#include "../config.h"

int main(int argc,char* argv[])
{
    if(argc != 2){
        cerr<<"Usage:"<<argv[0]<<"<Server Port>"<<endl;
        exit(1);
    }

 unsigned short servPort = atoi(argv[1]); 

namedWindow("recv",WINDOW_AUTOSIZE);
try{
    UDPSocket sock(servPort);

    char buffer[BUF_LEN];
    int recvMsgSize;
    string sourceAddress;
    unsigned short sourcePort;

    clock_t last_cycle = clock();

    while(1){
        do{
            recvMsgSize = sock.recvFrom(buffer,BUF_LEN,sourceAddress,sourcePort);
        }while (recvMsgSize > sizeof(int));
        int total_pack = ((int*)buffer)[0];//接收buffer 得到总包数

        cout<<"expecting length of packs: "<<total_pack<<endl;
        char *longbuf = new char[PACK_SIZE * total_pack];
        for (int i=0;i<total_pack;i++){//接收数据包，存在longbuf中
            recvMsgSize = sock.recvFrom(buffer,BUF_LEN,sourceAddress,sourcePort);
            if(recvMsgSize != PACK_SIZE){
                cerr<<"Received unexpected size pack: "<<recvMsgSize<<endl;
                continue;
            }
            memcpy(& longbuf[i*PACK_SIZE],buffer,PACK_SIZE);//注意存储的起始位置
        }

        cout<<"Received packet from"<<sourceAddress<<":"<<sourcePort<<endl;

        Mat rawData = Mat(1,PACK_SIZE*total_pack,CV_8UC1,longbuf);//图像转码
        Mat frame = imdecode(rawData,IMREAD_COLOR);

        if(frame.size().width == 0){
            cerr<<"decode failure!"<<endl;
            continue;
        }

        imshow("recv",frame);
        free(longbuf);
        //waitKey(1000);//显示图像
        string pic_name = "../image/img" + to_string(servPort) + ".jpg";
        imwrite(pic_name,frame);//重命名图像
        break;
    }
    }catch (SocketException & e) {
        cerr << e.what() << endl;
        exit(1);
    }

    destroyWindow("recv");
    return 0;
}