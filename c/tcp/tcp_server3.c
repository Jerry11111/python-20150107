#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include<malloc.h>
 
#define MAX_LINE 3
#define INET_ADDR_STR 16 
 
void _printf(char *ch, int len)
{
    char *a = malloc(len+1);
    bzero(a, sizeof(a));
    char *b = a;
    int j = 0;
    for(;j < len; j++){
        *b++ = *ch++; 
    }   
    printf("%s\n", a); 
    free(a);
}

void append3(char *a, char *b, int start, int len)
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
int test()
{
    struct sockaddr_in addr_server;     
    struct sockaddr_in addr_client;     
    char addr_client_buf[INET_ADDR_STR]; 
    socklen_t addr_client_len;
    int server_socket_fd;
    int client_socket_fd;
    char buf[MAX_LINE];     
    int port = 8000;
    int read_len;
    bzero((void *)&addr_server,sizeof(addr_server));
    addr_server.sin_family = AF_INET;   
    addr_server.sin_addr.s_addr = INADDR_ANY;   
    addr_server.sin_port = htons(port); 
    server_socket_fd = socket(AF_INET,SOCK_STREAM,0);   
    bind(server_socket_fd,(struct sockaddr *)&addr_server,sizeof(addr_server));
    listen(server_socket_fd,10);         
    printf("waiting ....\n");
	char * t = malloc(100);
    while(1)
    {
        client_socket_fd = accept(server_socket_fd,(struct sockaddr *)&addr_client,&addr_client_len);
		if( client_socket_fd < 0)
		{
			 perror("socket error\n");
		}
        printf("client_socket_fd  : %d\n", client_socket_fd);   //打印客户端发送过来的数据
        read_len = read(client_socket_fd,buf,MAX_LINE);    
		int t_len = 0;
		//while((read_len = read(client_socket_fd,buf,MAX_LINE)) > 0)
		//{
		//	append3(t, buf, 0, read_len);
		//	t_len += read_len;
		//	_printf(buf, read_len);	
		//	if( read_len < MAX_LINE)
		//	{
		//		break;	
		//	}
		//}
        inet_ntop(AF_INET,&addr_client.sin_addr,addr_client_buf,INET_ADDR_STR);      
        //将客户端传来地址转化为字符串
        printf("client IP is %s,port is %d\n",addr_client_buf,ntohs(addr_client.sin_port));
        printf("content is : %s\n", t);   //打印客户端发送过来的数据
        write(client_socket_fd,t,t_len);          //转换后发给客户端
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
int main(int argc,char **argv)
{
	test();
    return 0;
}
