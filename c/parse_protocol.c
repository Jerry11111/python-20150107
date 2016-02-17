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
#include <netinet/udp.h>
//#include <net/if_arp.h>
void test1();
void test2();
void parseETHER(char *buf);
void parseARP(char *buf);
void parseIP(char *buf);
void parseUDP(char *buf);
void parseDNS(char *buf);
void parseTCP(char *buf, struct ip *ip_hdr);
int main(int argc,char *argv[])
{
	test1();
    return 0;
}
struct arphdr2 {
        __be16          ar_hrd;         /* format of hardware address   */
        __be16          ar_pro;         /* format of protocol address   */
        unsigned char   ar_hln;         /* length of hardware address   */
        unsigned char   ar_pln;         /* length of protocol address   */
        __be16          ar_op;          /* ARP opcode (command)         */

         /*
          *      Ethernet looks like this : This bit is variable sized however...
          */
        unsigned char           ar_sha[ETH_ALEN];       /* sender hardware address      */
        unsigned char           ar_sip[4];              /* sender IP address            */
        unsigned char           ar_tha[ETH_ALEN];       /* target hardware address      */
        unsigned char           ar_tip[4];              /* target IP address            */

};
void parseARP(char *buf)
{
	struct arphdr2 * arp_hdr = (struct arphdr2 *)(buf + sizeof(struct ether_header));	
        unsigned char src_mac[18] = "";
        unsigned char dst_mac[18] = "";
        sprintf(src_mac,"%02x:%02x:%02x:%02x:%02x:%02x", arp_hdr->ar_sha[0], arp_hdr->ar_sha[1], arp_hdr->ar_sha[2], arp_hdr->ar_sha[3], arp_hdr->ar_sha[4], arp_hdr->ar_sha[5]);
        sprintf(dst_mac,"%02x:%02x:%02x:%02x:%02x:%02x", arp_hdr->ar_tha[0], arp_hdr->ar_tha[1], arp_hdr->ar_tha[2], arp_hdr->ar_tha[3], arp_hdr->ar_tha[4], arp_hdr->ar_tha[5]);
    	char sip[20]="";
    	char dip[20]="";
    	inet_ntop(AF_INET, (void *)&arp_hdr->ar_sip, sip, 16);
    	inet_ntop(AF_INET, (void *)&arp_hdr->ar_tip, dip, 16);
        printf("\n== ARP HEADER ==\n");
	int s = sizeof(struct arphdr2);
        printf("sizeof:%hu\n", s);
        printf("hardware type:%hu\n", ntohs(arp_hdr->ar_hrd));
        printf("protocol type:%hx\n", ntohs(arp_hdr->ar_pro));
        printf("hardware address length:%hu\n", arp_hdr->ar_hln);
        printf("protocol address length:%hu\n", arp_hdr->ar_pln);
        printf("op code:%hu\n", ntohs(arp_hdr->ar_op));
        // 后面几个字段没有，不知道什么原因？
        printf("sender hardware address:%s\n", src_mac);
        printf("sender IP address :%s\n", sip);
        printf("target hardware address:%s\n", dst_mac);
        printf("target IP address :%s\n", dip);
}
void parseETHER(char *buf)
{
        unsigned char src_mac[18] = "";
        unsigned char dst_mac[18] = "";
        struct ether_header *ip_h = (struct ether_header *)(buf);
	int ether_type = (int)htons(ip_h->ether_type);
        //printf("\ntype:%x\n", ether_type);
        //printf("data:%s, sizeof:%d\n", buf, s);
        //从buf里提取目的mac、源mac
        sprintf(dst_mac,"%02x:%02x:%02x:%02x:%02x:%02x", ip_h->ether_dhost[0], ip_h->ether_dhost[1], ip_h->ether_dhost[2], ip_h->ether_dhost[3], ip_h->ether_dhost[4], ip_h->ether_dhost[5]);
        sprintf(src_mac,"%02x:%02x:%02x:%02x:%02x:%02x", ip_h->ether_shost[0], ip_h->ether_shost[1], ip_h->ether_shost[2], ip_h->ether_shost[3], ip_h->ether_shost[4], ip_h->ether_shost[5]);
        printf("\n== ETHER HEADER ==\n");
        printf("MAC SRC:%s\n",src_mac);
        printf("MAC DEST:%s\n", dst_mac);
        printf("ether_type:%hu\n", ether_type);
    
}
void parseIP(char *buf)
{
    struct ip *ip_hdr = (struct ip*) (buf + sizeof(struct ether_header));
    unsigned int size_ip = ip_hdr->ip_hl * 4;
    printf("\n== IP HEADER ==\n");
    printf("IP Version: %u\n", ip_hdr->ip_v); //? Nthos or no nthos
    printf("Header Length: %u\n", ip_hdr->ip_hl); //? Nthos or no nthos
    printf("tos: %u\n", ip_hdr->ip_tos); //? Nthos or no nthos
    printf("Total Length: %hu\n", ntohs(ip_hdr->ip_len)); //? Nthos or no nthos
    printf("id: %hu\n", ntohs(ip_hdr->ip_id)); //? Nthos or no nthos
    printf("off: %hu\n", ntohs(ip_hdr->ip_off)); //? Nthos or no nthos
    printf("ttl: %hu\n", ip_hdr->ip_ttl); //? Nthos or no nthos
    printf("Protocol: %hu\n", ip_hdr->ip_p); //不需要使用ntohs转换
    printf("sum: %hu\n", ntohs(ip_hdr->ip_sum)); //不需要使用ntohs转换
    char sip[20]="";
    char dip[20]="";
    inet_ntop(AF_INET, (void *)&ip_hdr->ip_src, sip, 16);
    printf("source ip: %s\n", sip); //不需要使用ntohs转换
    inet_ntop(AF_INET, (void *)&ip_hdr->ip_dst, dip, 16);
    printf("destination ip: %s\n", dip); //不需要使用ntohs转换
	
}
void parseTCP(char *buf, struct ip *ip_hdr)
{
   // tcp
   // TCP Header
   printf("\n== TCP HEADER ==\n");
   struct tcphdr *tcp_hdr = (struct tcphdr*) (buf + sizeof(struct ether_header) + sizeof(struct ip));
   printf("\n Source Port: %hu" , ntohs(tcp_hdr->th_sport));
   printf("\n Destination Port: %hu" , ntohs(tcp_hdr->th_dport));
   //printf("\n Destination Port: %hu" , ntohs(tcp_hdr->dest));
   printf("\n seq: %hu" , ntohl(tcp_hdr->seq));
   printf("\n ack_seq: %hu" , ntohl(tcp_hdr->ack_seq));
   printf("\n doff: %hu" , tcp_hdr->doff);
   printf("\n urg: %hu" , tcp_hdr->urg);
   printf("\n ack: %hu" , tcp_hdr->ack);
   printf("\n psh: %hu" , tcp_hdr->psh);
   printf("\n rst: %hu" , tcp_hdr->rst);
   printf("\n syn: %hu" , tcp_hdr->syn);
   printf("\n fin: %hu" , tcp_hdr->fin);
   printf("\n window: %hu" , ntohl(tcp_hdr->window));
   printf("\n check: %hu" , ntohl(tcp_hdr->check));
   printf("\n urg_ptr: %hu" , ntohl(tcp_hdr->urg_ptr));
   char *data = (char*)(buf +sizeof(struct ether_header) + sizeof(struct ip) + tcp_hdr->doff * 4);
   //char *data = (char*)(buf +sizeof(struct ether_header) + sizeof(struct ip) + tcp_hdr->doff * 4);
   int data_size = ntohs(ip_hdr->ip_len) - ip_hdr->ip_hl * 4 - tcp_hdr->doff * 4 ;
   int doff_size = tcp_hdr->doff * 4;
   int tcp_hdr_size = sizeof(struct tcphdr);
   int ip_tcp_hdr_size = sizeof(struct ip) + tcp_hdr->doff * 4;
   int ether_ip_tcp_hdr_size = sizeof(struct ether_header) + sizeof(struct ip) + tcp_hdr->doff * 4;
   printf("\n data_size=%hu, doff_size =%hu, tcp_hdr_size =%hu, ip_tcp_hdr_size=%hu, ether_ip_tcp_hdr_size =%hu", data_size, doff_size, tcp_hdr_size, ip_tcp_hdr_size, ether_ip_tcp_hdr_size );
   printf("\n data size: %hu" , data_size);
   printf("\n data: %s" , data);
	
}
void parseUDP(char *buf)
{
   // UDP
   printf("\n== UDP HEADER ==\n");
   struct udphdr *udp_hdr = (struct udphdr*) (buf + sizeof(struct ether_header) + sizeof(struct ip));
   //printf("\n Source Port: %hu" , ntohs(udp_hdr->uh_sport));
   printf("\n Source Port: %hu" , ntohs(udp_hdr->source));
   printf("\n Destination Port: %hu" , ntohs(udp_hdr->dest));
   printf("\n len: %hu" , ntohs(udp_hdr->len));
   printf("\n check: %hu" , ntohs(udp_hdr->check));
   char *data = (char*)(buf +sizeof(struct ether_header) + sizeof(struct ip) + sizeof(struct udphdr));
   int data_size = ntohs(udp_hdr->len) - 8;
   printf("\n data size: %hu" , data_size);
   int d = sizeof(struct udphdr);
   printf("\n d: %hu" , d);
   printf("\n data: %s" , data);
   if( ntohs(udp_hdr->dest) == 53 || ntohs(udp_hdr->source) == 53 ){
	  parseDNS(buf);
   }

}
struct dns_header //DNS数据报：
{
	unsigned short id; //标识，通过它客户端可以将DNS的请求与应答相匹配；
	unsigned short flags; //标志：[ QR | opcode | AA| TC| RD| RA | zero | rcode ]
	unsigned short quests; //问题数目；
	unsigned short answers; //资源记录数目；
	unsigned short author; //授权资源记录数目；
	unsigned short addition; //额外资源记录数目；
}; 
struct dns_query
{
	unsigned char addr[16];
    unsigned short type;
    unsigned short class; 
};
struct dns_answer
{
	unsigned short name;
	unsigned short type;
	unsigned short class;
	unsigned short ttl;
	unsigned short length;
}
void parseDNS(char *buf)
{
     char *data = (char*)(buf +sizeof(struct ether_header) + sizeof(struct ip) + sizeof(struct udphdr));
     struct dns_header *dns_hdr = (struct dns_header *)data; 
	 printf("\n id: 0x%04x" , ntohs(dns_hdr->id));
     printf("\n flags: 0x%04x" , ntohs(dns_hdr->flags));
     printf("\n quests: %u" , ntohs(dns_hdr->quests));
     printf("\n answers: %u" , ntohs(dns_hdr->answers));
     printf("\n author: %u" , ntohs(dns_hdr->author));
     printf("\n addition: %u" , ntohs(dns_hdr->addition));
     char * addr = (char *) (data + 12);
     int i = 0;
	 char ad[1024] = "";
	 int index = 0;
	 int ad_index = 0;
	 while(*(addr + index) != '\0'){
		char count = *(addr + index);
		index++;
		int j = 0;
		 for(; j < count; j++){
			ad[ad_index]= *(addr + index );
			index++;
			ad_index++;
		 }
		 ad[ad_index] = '.';
			ad_index++;
		
	 }
	 ad_index--;
	 ad[ad_index]='\0';
     printf("\n ad: %s" , ad);
     while(*(addr + i) != '\0'){
         i++;
     }
     unsigned short type = *((unsigned short *)(addr + i + 1));
     unsigned short class = *((unsigned short *)(addr + i + 1 + 2));
     printf("\n addr: %s" , addr);
     printf("\n type: %d" , ntohs(type));
     printf("\n class: %d" , ntohs(class));
     //struct dns_query *query = (struct dns_query *)addr;
     //printf("\n addr: %s" , query->addr);
     //printf("\n type: %d" , ntohs(query->type));
     //printf("\n class: %d" , ntohs(query->class));

}
void test1()
{
    int i = 0;
    unsigned char buf[1024] = "";
    int sock_raw_fd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    while(1)
    {
        //获取链路层的数据帧
        recvfrom(sock_raw_fd, buf, sizeof(buf),0,NULL,NULL);
        struct ether_header *ip_h = (struct ether_header *)(buf);
	int ether_type = (int)htons(ip_h->ether_type);
        //parseETHER(buf);
        //判断是否为IP数据包
        if(ether_type==0x0800)
        {    
            struct ip *ip_hdr = (struct ip*) (buf + sizeof(struct ether_header));
            unsigned int size_ip = ip_hdr->ip_hl * 4;
            //parseIP(buf);
		if(ip_hdr->ip_p == 6)// tcp=6
		{
		   // tcp
		   // TCP Header
		  // parseTCP(buf, ip_hdr);
		}else if(ip_hdr->ip_p == 17)// UDP
		{
			// UDP
		  parseUDP(buf);
		}
        }//判断是否为ARP数据包
        else if(ether_type==0x0806)
        {
            //printf("______________ARP数据报_______________\n");
            //parseARP(buf);
            //printf("MAC:%s >> %s\n",src_mac,dst_mac);
        }//判断是否为RARP数据包
        else if(ether_type==0x8035)
        {
            printf("______________RARP数据报_______________\n");
            //printf("MAC:%s>>%s\n",src_mac,dst_mac);
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
