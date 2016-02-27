/*  
 * File:   main.c 
 * Author: tianshuai 
 * 
 * Created on 2011年11月29日, 下午10:34 
 * 
 * 主要实现：发送20个文本消息，然后再发送一个终止消息 
 */  
  
#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>  
#include <netdb.h>  
  
int port=6789;  
int main(int argc, char** argv) {  
    int socket_descriptor; //套接口描述字  
    int iter=0;  
    char buf[80];  
    struct sockaddr_in address;//处理网络通信的地址  
  
    bzero(&address,sizeof(address));  
    address.sin_family=AF_INET;  
    address.sin_addr.s_addr=inet_addr("127.0.0.1");//这里不一样  
    address.sin_port=htons(port);  
    //创建一个 UDP socket  
    socket_descriptor=socket(AF_INET,SOCK_DGRAM,0);//IPV4  SOCK_DGRAM 数据报套接字（UDP协议）  
	char *msg = "Hello World!\n";
    sprintf(buf, "msg\n");  
    sendto(socket_descriptor,buf,sizeof(buf),0,(struct sockaddr *)&address,sizeof(address));//发送stop 命令  
	bzero(buf, 80);
	recvfrom(socket_descriptor,buf,sizeof(buf),0,NULL,NULL);
	printf("%s\n", buf);
    close(socket_descriptor);  
    exit(0);  
    return (EXIT_SUCCESS);  
}  
