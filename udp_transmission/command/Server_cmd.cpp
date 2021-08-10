
#include "../lib/PracticalSocket.h" // For UDPSocket and SocketException
#include <iostream>          // For cout and cerr
#include <cstdlib>           // For atoi()
#include  <string>
#define BUF_LEN 65540 // Larger than maximum UDP packet size
#include "opencv2/opencv.hpp"
using namespace cv;
#include "../config.h"
int main(int argc, char * argv[]) {

    if (argc != 2) { // Test for correct number of parameters
        cerr << "Usage: " << argv[0] << " <Server Port>" << endl;
        exit(1);
    }

    unsigned short servPort = atoi(argv[1]); // First arg:  local port


    UDPSocket sock(servPort);

    char buffer[BUF_LEN]; // Buffer for echo string
    int recvMsgSize; // Size of received message
    string sourceAddress; // Address of datagram source
    unsigned short sourcePort; // Port of datagram source



    while (1) {
        // Block until receive message from a client
        recvMsgSize = sock.recvFrom(buffer, BUF_LEN, sourceAddress, sourcePort);
        
        cout << "Received packet from " << sourceAddress << ":" << sourcePort << endl;
        cout<<"buffer:"<<buffer<<endl;

        cout<<sizeof(buffer)<<endl;
        stringstream ss;
        ss<<buffer;
        string key = ss.str();
        cout<<key<<endl;
        if(key == "start"){
            cout<<"server_cmd:启动光电设备"<<endl;
            printf("success\n");
            break;
        }else if(key == "end"){
            cout<<"server_cmd:关闭光电设备"<<endl;
            printf("shut down\n");
            break;
        }else if(key == "img1"){
            cout<<"server_cmd:发送img1"<<endl;
            printf("send img1");
            break;
        }else if(key == "img2"){
            cout<<"server_cmd:发送img2"<<endl;
            printf("send img2");
            break;
        }else if(key == "msg1"){
            cout<<"server_cmd:发送msg1"<<endl;
            printf("send msg1");
            break;
        }else if(key == "msg2"){
            cout<<"server_cmd:发送msg2"<<endl;
            printf("send msg2");
            break;
        }else{
            cout<<"server_cmd:发送指令错误！"<<endl;
        }
    }
    
    return 0;
}
