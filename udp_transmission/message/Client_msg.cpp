
#include "../lib/PracticalSocket.h"      // For UDPSocket and SocketException
#include <iostream>               // For cout and cerr
#include <cstdlib>                // For atoi()
using namespace std;

#include "opencv2/opencv.hpp"
using namespace cv;
#include "../config.h"


int main(int argc, char * argv[]) {
    if ((argc < 11) || (argc > 11)) { // Test for correct number of arguments
        cerr << "Usage: " << argv[0] << " <Server> <Server Port><state> <Xmin> <Xmax> <Ymin> <Ymax><xpos><ypox><flag>\n";
        exit(1);
    }

    string servAddress = argv[1]; // First arg: server address
    unsigned short servPort = Socket::resolveService(argv[2], "udp");

     string state = argv[3];
    string xmin = argv[4];
    string xmax = argv[5];
    string ymin = argv[6];
    string  ymax = argv[7];
    string  xpos = argv[8];
    string  ypos = argv[9];
    string  flag = argv[10];
    string  spacing = " ";

    string  result = state + spacing + xmin + spacing +  xmax  + spacing + ymin  + spacing +  ymax  + spacing +  xpos  + spacing +  ypos  + spacing + flag;
    
    char sendbytes [150];
    strcpy(sendbytes,result.c_str());
    printf("client send: %s\n", result.c_str());  

    UDPSocket sock;
    
    sock.sendTo(sendbytes, sizeof(sendbytes), servAddress, servPort);

    return 0;
}
