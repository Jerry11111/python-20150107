#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
 
#define MAX_LINE 1024
#define INET_ADDR_STR 16 
 
int readn(int fd, void *vptr, size_t n)
{
	size_t nleft;
	ssize_t nread;
	char *ptr;
	ptr = vptr;
	nleft = n;
	while(nleft > 0)
	{
		if((nread = read(fd, ptr, nleft)) < 0){
			if(errno == EINTR){
				nread = 0;
			}else{
				return -1;
			}
		}else if(nread == 0){
			break;
		}
		nleft -= nread;
		ptr += nread;
	}
	return n -nleft;
}

int main(int argc,char **argv)
{
    struct sockaddr_in addr_server;     //服务器通信地址结构
    struct sockaddr_in addr_client;     //保存客户端通信地址结构
    char addr_client_buf[INET_ADDR_STR]; //存储客户端地址的缓冲区
    socklen_t addr_client_len;
    int server_socket_fd;
    int client_socket_fd;
    char buf[MAX_LINE];     //存储传送内容的缓冲区
    int port = 8000;
    int read_len;
    bzero((void *)&addr_server,sizeof(addr_server));
    addr_server.sin_family = AF_INET;   //使用IPV4通信域
    addr_server.sin_addr.s_addr = INADDR_ANY;   //服务器可以接受任意地址
    addr_server.sin_port = htons(port); //端口转换为网络字节序
    // 1. 创建套接字, 使用TCP协议
    server_socket_fd = socket(AF_INET,SOCK_STREAM,0);   
	// 2. 将套接字绑定到一个本地地址和端口上
    bind(server_socket_fd,(struct sockaddr *)&addr_server,sizeof(addr_server));
	// 3. 将套接字设置为监听模式
    listen(server_socket_fd,10);         
    printf("waiting ....\n");
    while(1)
    {
	    // 4.接收连接请求 
        client_socket_fd = accept(server_socket_fd,(struct sockaddr *)&addr_client,&addr_client_len);
        // 5. 读取客户端发送来的信息 
        read_len = read(client_socket_fd,buf,MAX_LINE);    
        inet_ntop(AF_INET,&addr_client.sin_addr,addr_client_buf,INET_ADDR_STR);      
        //将客户端传来地址转化为字符串
        printf("client IP is %s,port is %d\n",addr_client_buf,ntohs(addr_client.sin_port));
        printf("content is : %s\n", buf);   //打印客户端发送过来的数据
       // my_fun(buf);
        write(client_socket_fd,buf,read_len);          //转换后发给客户端
		// 关闭客户端socket 
        close(client_socket_fd);
    }
    printf("buf = %s\n",buf);
	// 关闭服务端socket
    if((close(server_socket_fd)) == -1)
    {
        perror("fail to close\n");
        exit(1);
    }
    return 0;
}
