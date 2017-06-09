#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
 
#define MAX_LINE 1024
#define INET_ADDR_STR 16 
void demo()
{
    struct sockaddr_in saddr;     
    struct sockaddr_in caddr;     
    char caddr_buf[INET_ADDR_STR]; 
    socklen_t caddr_len;
    int sfd;
    int cfd;
    char buf[MAX_LINE];     
    int port = 9999;
    int read_len;
    bzero((void *)&saddr, sizeof(saddr));
    saddr.sin_family = AF_INET;   
    saddr.sin_addr.s_addr = INADDR_ANY;   
    saddr.sin_port = htons(port); 
    if((sfd = socket(AF_INET, SOCK_STREAM,0)) == -1)   
    {
	perror("socket error");	
	return;
    }
    if(bind(sfd,(struct sockaddr *)&saddr, sizeof(saddr)) == -1)
    {
	perror("bind error");
	return;
    }
    if(listen(sfd, 10) == -1)         
    {
	perror("listen error");	
	return;
    }
    printf("server start at %d ....\n", port);
    while(1)
    {
        cfd = accept(sfd, (struct sockaddr *)&caddr, &caddr_len);
	if(cfd < 0)
	{
	    perror("accept error");
	    exit(1);
	}
        read_len = read(cfd, buf, MAX_LINE);    
        printf("%s\n", buf);   
        write(cfd, buf, read_len);          
        close(cfd);
    }
    if((close(sfd)) == -1)
    {
        perror("close server socket error");
        exit(1);
    }

}
int main(int argc,char **argv)
{
    demo();
    return 0;
}
