#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<stdlib.h>
#include<string.h>

int main()
{
        struct sockaddr_in sin;
        struct sockaddr_in pin;
        int socketfd;
        int tmpsock;
        int size;
        char buf[10000];
        int len;
        int total = 0;
        if ((socketfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
                perror("socket error\n");
                exit(1);
        }

        memset(buf, 0, sizeof(buf));
        memset(&sin, 0, sizeof(sin));
        sin.sin_family = AF_INET;
        sin.sin_addr.s_addr = INADDR_ANY;
        sin.sin_port = htons(8000);

        if (bind(socketfd, (struct sockaddr*)&sin, sizeof(sin)) < 0)
        {
                perror("bind error\n");
                exit(1);
        }

        if (listen(socketfd, 20) < 0)
        {
                perror("listen error\n");
                exit(1);
        }

        printf("accept...\n");

        if ((tmpsock = accept(socketfd, (struct sockaddr*)&pin, &size)) < 0)
        {
                perror("accept error\n");
                exit(1);
        }

        while ((len = read(tmpsock, buf, 10000))  > 0)
        {
                printf("buflen = %d\n", strlen(buf));
                printf("len = %d\n", len);
                total += len;
                memset(buf, 0, sizeof(buf));
        }

        printf("final len = %d\n", total);
        close(tmpsock);
        return 0;
}
