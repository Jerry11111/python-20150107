#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#define MAX_LINE 1024
 
int main(int argc,char **argv)
{
    struct sockaddr_in sin;     //服务器的地址
    char buf[MAX_LINE];
    int sfd;
    int port = 9999;
    char *str = "teststring";
    char *serverIP = "127.0.0.1";
    if(argc > 1)
    {
        str = argv[1];  //读取用户输入的字符串
    }
    bzero((void *)&sin,sizeof(sin));
    sin.sin_family = AF_INET;   //使用IPV4地址族
    inet_pton(AF_INET,serverIP,(void *)&(sin.sin_addr));
    sin.sin_port = htons(port);
    // 1. 创建socket套接字 
    sfd = socket(AF_INET,SOCK_STREAM,0);
    // 2. 连接服务端 
    connect(sfd,(struct sockaddr *)&(sin),sizeof(sin));
    printf("str = %s\n" , str);
    write(sfd , str , strlen(str) + 1);
    read(sfd , buf , MAX_LINE);
    printf("recive from server: %s\n" , buf);
    // 关闭socket 
    close(sfd);
    return 0;
}
