#include "../lib/PracticalSocket.h"      // For UDPSocket and SocketException
#include <iostream>               // For cout and cerr
#include <cstdlib>                // For atoi()

using namespace std;

#include "opencv2/opencv.hpp"
using namespace cv;
#include "../config.h"


int main(int argc,char* argv[]){

    if((argc<4)||(argc>4)){
        cerr<<"Usage:"<<argv[0]<<"<Server><Server Port>\n";
        exit(1);
    }

    string servAddress = argv[1];
    unsigned short servPort = Socket::resolveService(argv[2],"udp");

    

    try{
        UDPSocket sock;
        int jpegual = ENCODE_QUALITY;

        Mat frame,send;
        vector<uchar> encoded;

        frame = imread(argv[3]);//图像地址
        //if(frame.size().width==0)continue;
        resize(frame,send,Size(FRAME_WIDTH,FRAME_HEIGHT),0,0,INTER_LINEAR);
        vector<int> compression_params;
        compression_params.push_back(IMWRITE_JPEG_QUALITY);//写入质量
        compression_params.push_back(jpegual);//图像质量

         imencode(".jpg",send,encoded,compression_params);
         imshow("send",send);
         int total_pack = 1 + (encoded.size()-1)/PACK_SIZE; //图像拆包

         int ibuf[1];
        ibuf[0] = total_pack;
        sock.sendTo(ibuf, sizeof(int), servAddress, servPort); //发送包总数

        for (int i = 0; i < total_pack; i++)
            sock.sendTo( & encoded[i * PACK_SIZE], PACK_SIZE, servAddress, servPort);//发送剩余数据包

    }catch (SocketException & e) {
        cerr << e.what() << endl;
        exit(1);
    }
    return 0;
}