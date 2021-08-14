#include "../lib/PracticalSocket.h" // For UDPSocket and SocketException
#include <iostream>          // For cout and cerr
#include <cstdlib>           // For atoi()
#include <fstream>
#define BUF_LEN 65540 // Larger than maximum UDP packet size

#include "opencv2/opencv.hpp"
using namespace cv;
#include "../config.h"
#include <typeinfo>
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
        
        cout<<"buffer type:"<<typeid(buffer).name()<<endl;

        cout<<sizeof(buffer)<<endl;

        
        if(sizeof(buffer)> 20) {
            ofstream outfile;
            outfile.open("../message/msg"+to_string(servPort)+".txt");
            outfile<<buffer<<endl;
            outfile.close();
            cout<<"保存完毕"<<endl;

            

            vector<float> array;
            stringstream ss(buffer);
            //cout<<ss<<endl;
            float temp;
            while (ss>>temp )
                array.push_back(temp);
            cout<<sizeof(array)<<endl;
           for (auto const& value :array)
                cout<<value<<";";
            cout<<endl;

            if(array[0]==0) {
                cout<<"系统未启动"<<endl;
            }else if(array[0]==1){

                cout<<"系统工作正常"<<endl;
            }else{
                cout<<"系统工作异常"<<endl;
                printf("侦查已停止");
                return 1;
            }
            cout<<"-------result-------"<<endl;
            cout<<"state:"<<array[0]<<endl;
            cout<<"xmin:"<<array[1]<<endl;
            cout<<"xmax:"<<array[2]<<endl;
            cout<<"ymin:"<<array[3]<<endl;
            cout<<"ymax:"<<array[4]<<endl;
            cout<<"xpos:"<<array[5]<<endl;
            cout<<"ypos:"<<array[6]<<endl;
            cout<<"flag:"<<array[7]<<endl;
            cout<<"-------end-------"<<endl;
            break;
        }

    }

    return 0;
}
