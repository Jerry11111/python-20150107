



#define MAX_LINE 1024 
#define INET_ADDR_STR 16 
int main(int argc, char **argv) {
	struct sockaddr_in addr_server;
	struct sockaddr_in addr_client;
	char addr_client_buf[INET_ADDR_STR];
	socklen_t addr_client_len;
	int sock_fd;
	int client_sock_fd;
	char buf[MAX_LINE];
	// 1. 创建套接字
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);	
	// 2. 将套接字绑定到一个本地地址和端口上
	bind(sock_fd, &addr_server, sizeof(addr_server));
	// 3. 将套接字设置为监听模式
	listen(sock_fd, 10);
	printf("waiting ...\n")
	while(1)
	{
		client_sock_fd = accept(sock_fd, &addr_client, &addr_client_len);
		read(client_sock_fd, buf, MAX_LINE);
		inet_ntop(AF_INET,&addr_client.sin_addr, addr_client_buf, INET_ADDR_STR);
        
	}
   
}
