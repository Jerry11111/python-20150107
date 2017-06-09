#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#define MAX_LINE 1024
 
int main(int argc,char **argv)
{
    struct sockaddr_in sin;     
    char buf[MAX_LINE];
    int sfd;
    int port = 9999;
    char *str = "teststring";
    char *serverIP = "localhost";
    if(argc > 1)
    {
        str = argv[1];  
    }
    bzero((void *)&sin,sizeof(sin));
    sin.sin_family = AF_INET;   
    inet_pton(AF_INET,serverIP,(void *)&(sin.sin_addr));
    sin.sin_port = htons(port);
    sfd = socket(AF_INET,SOCK_STREAM,0);
    if(connect(sfd,(struct sockaddr *)&(sin),sizeof(sin)) < 0)
	{
		perror("connect error");
		exit(0);
	}
    printf("str = %s\n" , str);
    write(sfd , str , strlen(str) + 1);
    read(sfd , buf , MAX_LINE);
    printf("recive from server: %s\n" , buf);
    close(sfd);
    return 0;
}
