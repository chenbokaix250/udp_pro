#include "../lib/PracticalSocket.h"      // For UDPSocket and SocketException
#include <iostream>               // For cout and cerr
#include <cstdlib>                // For atoi()
using namespace std;

#include "opencv2/opencv.hpp"
using namespace cv;
#include "../config.h"


int main(int argc, char * argv[]) {
    if ((argc < 4) || (argc > 4)) { // Test for correct number of arguments
        cerr << "Usage: " << argv[0] << " <Server> <Server Port> <word>\n";
        exit(1);
    }

    string servAddress = argv[1]; // First arg: server address
    unsigned short servPort = Socket::resolveService(argv[2], "udp");

    string word = argv[3];
    
    char sendbytes [15];
    strcpy(sendbytes,word.c_str());
    printf("client send: %s\n", word.c_str());  

    UDPSocket sock;
    if(word == "start"){
        sock.sendTo(sendbytes, sizeof(sendbytes), servAddress, servPort);
        cout<<"client_cmd:发送启动命令"<<endl;
        printf("success!\n");
    }else if(word == "end"){
        sock.sendTo(sendbytes, sizeof(sendbytes), servAddress, servPort);
        cout<<"client_cmd:发送停止命令"<<endl;
        printf("shut down!\n");
    }else if(word == "msg1"){
        sock.sendTo(sendbytes, sizeof(sendbytes), servAddress, servPort);
        cout<<"client_cmd:发送msg1"<<endl;
        
    }else if(word == "msg2"){
        sock.sendTo(sendbytes, sizeof(sendbytes), servAddress, servPort);
        cout<<"client_cmd:发送msg2"<<endl;
        
    }else if(word == "img1"){
        sock.sendTo(sendbytes, sizeof(sendbytes), servAddress, servPort);
        cout<<"client_cmd:发送img1"<<endl;
        
    }else if(word == "img2"){
        sock.sendTo(sendbytes, sizeof(sendbytes), servAddress, servPort);
        cout<<"client_cmd:发送img2"<<endl;
        
    }else{
        sock.sendTo(sendbytes, sizeof(sendbytes), servAddress, servPort);
        cout<<"client_cmd:指令错误！"<<endl;
        printf("err info!\n");
    }




    return 0;
}
