#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
 
#define MAX_LINE 1024
#define INET_ADDR_STR 16 
 
 
void my_fun(char *p)
{
    if(p == NULL)
    {
        return;
    }
    for( ; *p != '\0' ; p++)
    {
        if((*p >= 'a') && (*p <= 'z'))
        {
            *p = *p - 32;
        }
    }
    return;
}
// tcp demo,一次性读取所有的消息
void demo()
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

}
void _printf(char *ch, int len)
{
    char *a = malloc(len+1);
    bzero(a, sizeof(a));
    char *b = a;
    int j = 0;
    for(;j < len; j++){
        *b++ = *ch++; 
    }   
    printf("buf=%s, len=%d\n", a, len); 
    free(a);
}

void append(char *a, char *b, int start, int len)
{
    while (*a != '\0') {   
        a++;  
    }   
    b = b + start;
    int i = 0;
    while ((i++ < len) && (*a++ = *b++) != '\0') {   
        ;
    }
    *a = '\0';
}
// 读取大量的消息
void start()
{
    struct sockaddr_in addr_server;     //服务器通信地址结构
    struct sockaddr_in addr_client;     //保存客户端通信地址结构
    char addr_client_buf[16]; //存储客户端地址的缓冲区
    socklen_t addr_client_len;
    int server_socket_fd;
    int client_socket_fd;
    char buf[MAX_LINE];     //存储传送内容的缓冲区
    int port = 8000;
    int read_len = -1;
    bzero((void *)&addr_server,sizeof(addr_server));
    addr_server.sin_family = AF_INET;   //使用IPV4通信域
    addr_server.sin_addr.s_addr = INADDR_ANY;   //服务器可以接受任意地址
    addr_server.sin_port = htons(port); //端口转换为网络字节序
    // 1. 创建套接字, 使用TCP协议
    if((server_socket_fd = socket(AF_INET,SOCK_STREAM,0)) == -1)
	{
		perror("socket error");   
		exit(1);
	}
	// 2. 将套接字绑定到一个本地地址和端口上
    if(bind(server_socket_fd,(struct sockaddr *)&addr_server,sizeof(addr_server)) == -1)
	{
		perror("bind error");
		exit(1);
	}
	// 3. 将套接字设置为监听模式
    if((listen(server_socket_fd,10)) == -1)
	{
		perror("listen error");         
		exit(1);
	}
    printf("waiting ...\n");
    while(1)
    {
	    // 4.接收连接请求 
        if((client_socket_fd = accept(server_socket_fd,(struct sockaddr *)&addr_client,&addr_client_len)) == -1)
		{
			perror("accept error");
		    exit(1);
		}
        // 5. 读取客户端发送来的信息 
		char * t = malloc(1000);
		int t_len = 0;
		// 读取的字符小于MAX最退出, 否则下次读取会阻塞
		while((read_len = read(client_socket_fd,buf,MAX_LINE)) > 0)
		{
			append(t, buf, 0, read_len);
			//printf("t=%s\n", t);
			t_len += read_len;
			_printf(buf, read_len);	
		   	//printf("read_len=%d\n", read_len);
			if( read_len < MAX_LINE)
			{
				break;	
			}
		}
        inet_ntop(AF_INET,&addr_client.sin_addr,addr_client_buf,INET_ADDR_STR);      
        //将客户端传来地址转化为字符串
        printf("client_ip=%s, client_port=%d, msg=%s\n", addr_client_buf, ntohs(addr_client.sin_port), t);
        write(client_socket_fd,t,t_len);          //转换后发给客户端
		// 关闭客户端socket 
        if((close(client_socket_fd)) == -1)
		{
			perror("close error");
			exit(1);
		}
    }
    printf("buf = %s\n",buf);
	// 关闭服务端socket
    if((close(server_socket_fd)) == -1)
    {
        perror("fail to close");
        exit(1);
    }

}
void start2()
{
    struct sockaddr_in addr_server;     //服务器通信地址结构
    struct sockaddr_in addr_client;     //保存客户端通信地址结构
    char addr_client_buf[16]; //存储客户端地址的缓冲区
    socklen_t addr_client_len;
    int server_socket_fd;
    int client_socket_fd;
	int buf_len = 1000;
    char buf[buf_len];     //存储传送内容的缓冲区
    int port = 8000;
    bzero((void *)&addr_server,sizeof(addr_server));
    addr_server.sin_family = AF_INET;   //使用IPV4通信域
    addr_server.sin_addr.s_addr = INADDR_ANY;   //服务器可以接受任意地址
    addr_server.sin_port = htons(port); //端口转换为网络字节序
    // 1. 创建套接字, 使用TCP协议
    if((server_socket_fd = socket(AF_INET,SOCK_STREAM,0)) == -1)
	{
		perror("socket error");   
		exit(1);
	}
	// 2. 将套接字绑定到一个本地地址和端口上
    if(bind(server_socket_fd,(struct sockaddr *)&addr_server,sizeof(addr_server)) == -1)
	{
		perror("bind error");
		exit(1);
	}
	// 3. 将套接字设置为监听模式
    if((listen(server_socket_fd,10)) == -1)
	{
		perror("listen error");         
		exit(1);
	}
    printf("waiting ...\n");
    while(1)
    {
	    // 4.接收连接请求 
        if((client_socket_fd = accept(server_socket_fd,(struct sockaddr *)&addr_client,&addr_client_len)) == -1)
		{
			perror("accept error");
		    exit(1);
		}
        // 5. 读取客户端发送来的信息 
		char * t = malloc(1000);
		int t_len = 0;
        int read_len = -1;
		// 读取的字符小于MAX最退出, 否则下次读取会阻塞
		while((read_len = read(client_socket_fd,buf,buf_len)) > 0)
		{
			append(t, buf, 0, read_len);
			//printf("t=%s\n", t);
			t_len += read_len;
			_printf(buf, read_len);	
		   	//printf("read_len=%d\n", read_len);
			if( read_len < MAX_LINE)
			{
				break;	
			}
		}
        inet_ntop(AF_INET,&addr_client.sin_addr,addr_client_buf,INET_ADDR_STR);      
        //将客户端传来地址转化为字符串
        printf("client_ip=%s, client_port=%d, msg=%s\n", addr_client_buf, ntohs(addr_client.sin_port), t);
        write(client_socket_fd,t,t_len);          //转换后发给客户端
		// 关闭客户端socket 
        if((close(client_socket_fd)) == -1)
		{
			perror("close error");
			exit(1);
		}
    }
    printf("buf = %s\n",buf);
	// 关闭服务端socket
    if((close(server_socket_fd)) == -1)
    {
        perror("fail to close");
        exit(1);
    }

}
int main(int argc,char **argv)
{
	start();
    return 0;
}
