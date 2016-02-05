#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/ether.h>
#include <net/ethernet.h>
#include <unistd.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <netinet/ip.h>
#include <netinet/if_ether.h>
#include <net/if_arp.h>
#include <netpacket/packet.h>
#include <net/if.h>
#include <netinet/tcp.h>
void test1();
void test2();
int main(int argc,char *argv[])
{
	test1();
    return 0;
}
void test1()
{
    int i = 0;
    unsigned char buf[1024] = "";
    int sock_raw_fd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    struct ether_header *ip_h = NULL;
    while(1)
    {
        unsigned char src_mac[18] = "";
        unsigned char dst_mac[18] = "";
        //获取链路层的数据帧
        recvfrom(sock_raw_fd, buf, sizeof(buf),0,NULL,NULL);
		int s = sizeof(buf);
        ip_h = (struct ether_header *)(buf);
		int ether_type = (int)htons(ip_h->ether_type);
        printf("type:%x\n", ether_type);
        printf("data:%s, sizeof:%d\n", buf, s);
        //从buf里提取目的mac、源mac
        sprintf(dst_mac,"%02x:%02x:%02x:%02x:%02x:%02x", ip_h->ether_dhost[0], ip_h->ether_dhost[1], ip_h->ether_dhost[2], ip_h->ether_dhost[3], ip_h->ether_dhost[4], ip_h->ether_dhost[5]);
        sprintf(src_mac,"%02x:%02x:%02x:%02x:%02x:%02x", ip_h->ether_shost[0], ip_h->ether_shost[1], ip_h->ether_shost[2], ip_h->ether_shost[3], ip_h->ether_shost[4], ip_h->ether_shost[5]);
        //判断是否为IP数据包
        if(ether_type==0x0800)
        {    
            printf("______________IP数据报_______________\n");
            printf("MAC:%s >> %s\n",src_mac,dst_mac);
            struct ip *ip_hdr = (struct ip*) (buf + sizeof(struct ether_header));
            unsigned int size_ip = ip_hdr->ip_hl * 4;
            printf("IP Version: %u\n", ip_hdr->ip_v); //? Nthos or no nthos
            printf("Header Length: %u\n", ip_hdr->ip_hl); //? Nthos or no nthos
            printf("Total Length: %hu\n", ntohs(ip_hdr->ip_len)); //? Nthos or no nthos
            printf("Protocol: %hu\n", ip_hdr->ip_p); //不需要使用ntohs转换
            char sip[20]="";
            char dip[20]="";
            inet_ntop(AF_INET, (void *)&ip_hdr->ip_src, sip, 16);
            printf("source ip: %s\n", sip); //不需要使用ntohs转换
            inet_ntop(AF_INET, (void *)&ip_hdr->ip_dst, dip, 16);
            printf("destination ip: %s\n", dip); //不需要使用ntohs转换
           // tcp
           // TCP Header
           printf("\n== TCP HEADER ==\n");
           struct tcphdr *tcp_hdr = (struct tcphdr*) (buf + sizeof(struct ether_header) + sizeof(struct ip));
           printf("\n Source Port: %hu" , ntohs(tcp_hdr->th_sport));
           printf("\n Destination Port: %hu" , ntohs(tcp_hdr->th_dport));
           printf("\n fin: %hu" , tcp_hdr->fin);
           printf("\n urg: %hu" , tcp_hdr->urg);
           printf("\n ack_seq: %hu" , ntohl(tcp_hdr->ack_seq));
        }//判断是否为ARP数据包
        else if(ether_type==0x0806)
        {
            printf("______________ARP数据报_______________\n");
            printf("MAC:%s >> %s\n",src_mac,dst_mac);
        }//判断是否为RARP数据包
        else if(ether_type==0x8035)
        {
            printf("______________RARP数据报_______________\n");
            printf("MAC:%s>>%s\n",src_mac,dst_mac);
        }
    }
}
void test2()
{
    int i = 0;
    unsigned char buf[1024] = "";
    int sock_raw_fd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    while(1)
    {
        unsigned char src_mac[18] = "";
        unsigned char dst_mac[18] = "";
        //获取链路层的数据帧
        recvfrom(sock_raw_fd, buf, sizeof(buf),0,NULL,NULL);
		int s = sizeof(buf);
        printf("data:%s, sizeof:%d\n", buf, s);
        //从buf里提取目的mac、源mac
        sprintf(dst_mac,"%02x:%02x:%02x:%02x:%02x:%02x", buf[0], buf[1], buf[2], buf[3], buf[4], buf[5]);
        sprintf(src_mac,"%02x:%02x:%02x:%02x:%02x:%02x", buf[6], buf[7], buf[8], buf[9], buf[10], buf[11]);
        //判断是否为IP数据包
        if(buf[12]==0x08 && buf[13]==0x00)
        {    
            printf("______________IP数据报_______________\n");
            printf("MAC:%s >> %s\n",src_mac,dst_mac);
        }//判断是否为ARP数据包
        else if(buf[12]==0x08 && buf[13]==0x06)
        {
            printf("______________ARP数据报_______________\n");
            printf("MAC:%s >> %s\n",src_mac,dst_mac);
        }//判断是否为RARP数据包
        else if(buf[12]==0x80 && buf[13]==0x35)
        {
            printf("______________RARP数据报_______________\n");
            printf("MAC:%s>>%s\n",src_mac,dst_mac);
        }
    }
}
