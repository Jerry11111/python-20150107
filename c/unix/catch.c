 #include <stdio.h>
 #include <stdlib.h>
 #include <netinet/in.h>
 #include <unistd.h>
 #include <sys/socket.h>
 #include <arpa/inet.h>
 #include <string.h>
 #include <linux/if_ether.h>
 #include <linux/ip.h>
//#define ETH_P_IP "127.0.0.1"
int main(int argc, char** argv)
{
while(1)
{
	/*创建接受Raw Socket*/
//int recvsd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_IP));
int recvsd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
if(recvsd < 0){
    perror("raw socket() error");
    return 0;
}else
    printf("create raw socket successfully\n");
 
/*处理链路层数据*/
char buffer[2048];
struct iphdr* ip_reply;
char *iphead, *p;
int n = 0;
if((n = recvfrom(recvsd, buffer, 2048, 0, NULL, NULL)) < 42){
    printf("Too short\n");
}else{
    iphead = buffer + 14;          //Mac头部14字节
    p = iphead + 12;               //ip头部的source从12字节开始
    ip_reply = (struct iphdr*)iphead;
    //if(ntohs(ip_reply->id) == 3893){
        printf("IP:%d.%d.%d.%d => %d.%d.%d.%d\n",
                        p[0]&0XFF,p[1]&0XFF,p[2]&0XFF,p[3]&0XFF,
                         p[4]&0XFF,p[5]&0XFF,p[6]&0XFF,p[7]&0XFF);
     // }
}	
sleep(1);//等待一秒 
}
}
