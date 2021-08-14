１、socket函数：为了执行网络输入输出，一个进程必须做的第一件事就是调用socket函数获得一个文件描述符。

-----------------------------------------------------------------
 #include <sys/socket.h>
 int socket(int family,int type,int protocol); 　　　
  　　 　返回：非负描述字－－－成功　　　-1－－－失败
 -----------------------------------------------------------------

第一个参数指明了协议簇，目前支持5种协议簇，最常用的有AF_INET(IPv4协议)和AF_INET6(IPv6协议)；第二个参数指明套接口类型，有三种类型可选：SOCK_STREAM(字节流套接口)、SOCK_DGRAM(数据报套接口)和SOCK_RAW(原始套接口)；如果套接口类型不是原始套接口，那么第三个参数就为0。


2、bind函数：为套接口分配一个本地IP和协议端口，对于网际协议，协议地址是32位IPv4地址或128位IPv6地址与16位的TCP或UDP端口号的组合；如指定端口为0，调用bind时内核将选择一个临时端口，如果指定一个通配IP地址，则要等到建立连接后内核才选择一个本地IP地址。

-------------------------------------------------------------------
#include <sys/socket.h> 　
 int bind(int sockfd, const struct sockaddr * server, socklen_t addrlen);
 返回：0－－－成功　　　-1－－－失败　
 -------------------------------------------------------------------

　　第一个参数是socket函数返回的套接口描述字；第二和第第三个参数分别是一个指向特定于协议的地址结构的指针和该地址结构的长度。


３、recvfrom函数：UDP使用recvfrom()函数接收数据，他类似于标准的read()，但是在recvfrom()函数中要指明目的地址。

-------------------------------------------------------------------
#include <sys/types.h> 　
#include <sys/socket.h> 　
ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags, struct sockaddr * from, size_t *addrlen);
 返回接收到数据的长度－－－成功　　　-1－－－失败　
 -------------------------------------------------------------------

　　前三个参数等同于函数read()的前三个参数，flags参数是传输控制标志。最后两个参数类似于accept的最后两个参数。


4、sendto函数：UDP使用sendto()函数发送数据，他类似于标准的write()，但是在sendto()函数中要指明目的地址。

-------------------------------------------------------------------
#include <sys/types.h> 　
#include <sys/socket.h> 　
ssize_t sendto(int sockfd, const void *buf, size_t len, int flags, const struct sockaddr * to, int addrlen);
 返回发送数据的长度－－－成功　　　-1－－－失败　
 -------------------------------------------------------------------

　　前三个参数等同于函数read()的前三个参数，flags参数是传输控制标志。参数to指明数据将发往的协议地址，他的大小由addrlen参数来指定。