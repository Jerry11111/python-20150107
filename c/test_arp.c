#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/if_ether.h>
#include <net/if_arp.h>
#include <netpacket/packet.h>
#include <net/if.h>
#include <net/ethernet.h>
#include <arpa/inet.h>

#define BUFLEN 42
unsigned char* mactoch(char *mac)
{
   unsigned char addr[6];
   bzero(addr, 6);
   unsigned char *str = (unsigned char *) malloc(6);
   memset(str, 0, 6);
   sscanf(mac,"%hhx:%hhx:%hhx:%hhx:%hhx:%hhx",&addr[0],&addr[1],&addr[2],&addr[3],&addr[4],&addr[5]); 
   str = addr;
   printf("mac = %s\n", mac);
   //printf("addr = %s\n", str);
   printf("mac[] = %02x:%02x:%02x:%02x:%02x:%02x\n",addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);
   //printf("macp[] = %x\n",*str);
   //printf("macp[] = %x:%x:%x:%x:%x:%x\n",*str, *(str + 1), *(str + 2), *(str + 3), *(str + 4), *(str + 5));
   return str;
}
void testm()
{
    char *mac = "00:0c:29:15:61:80";
    unsigned char *str = mactoch(mac);
    printf("macp[] = %02x:%02x:%02x:%02x:%02x:%02x\n",*str, *(str + 1), *(str + 2), *(str + 3), *(str + 4), *(str + 5));

}
void build_arp(char *buf, unsigned char *ether_src_mac, unsigned char *ether_dst_mac, unsigned char *arp_src_mac, unsigned char *arp_dst_mac, char *src_ip, char *dst_ip )
{
    //ether_src_mac =  mactoch(ether_src_mac);
    //ether_dst_mac =  mactoch(ether_dst_mac);
    //arp_src_mac =  mactoch(arp_src_mac);
    //arp_dst_mac =  mactoch(arp_dst_mac);
    //开始填充，构造以太头部
    struct ether_header *eth = (struct ether_header*)buf;
    memcpy(eth->ether_dhost, ether_dst_mac, ETH_ALEN); 
    memcpy(eth->ether_shost, ether_src_mac, ETH_ALEN);
    eth->ether_type = htons(ETHERTYPE_ARP);

    //手动开始填充用ARP报文首部
    struct ether_arp* arp=(struct ether_arp*)(buf + sizeof(struct ether_header));
    arp->arp_hrd = htons(ARPHRD_ETHER); //硬件类型为以太网
    arp->arp_pro = htons(ETHERTYPE_IP); //协议类型为IP
    //硬件地址长度和IPV4地址长度分别是6字节和4字节
    arp->arp_hln = ETH_ALEN;
    arp->arp_pln = 4;
    //操作码，这里我们发送ARP请求
    arp->arp_op = htons(ARPOP_REQUEST);
    //填充发送端的MAC和IP地址
    memcpy(arp->arp_sha, arp_src_mac, ETH_ALEN);
    struct in_addr s;  // IPv4地址结构体
    struct in_addr t;  // IPv4地址结构体
    inet_pton(AF_INET, src_ip, (void *)&s);
    memcpy(arp->arp_spa, &s.s_addr, 4);
    //填充目的端的IP地址，MAC地址不用管
    inet_pton(AF_INET, dst_ip, (void *)&t);
    memcpy(arp->arp_tpa, &t.s_addr, 4);
    printf("dst_ip = %x\n", t.s_addr);
    printf("dst_ip = %s\n", dst_ip);
}
void send_arp()
{
    struct sockaddr_ll toaddr;
    char buf[BUFLEN]={0};
    int skfd,n;
    if(0 > (skfd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL)))){
            perror("Create Error");
            exit(1);
    }
    bzero(&toaddr, sizeof(toaddr));
    toaddr.sll_family = PF_PACKET;
    toaddr.sll_ifindex = if_nametoindex("eth0");// 必不可少
    printf("nsll_ifindex  = %d\n", if_nametoindex("eth0"));
    //char ether_src_mac[ETH_ALEN]= {0xff,0xff,0xff,0xff,0xff,0xf0};
    char ether_src_mac[ETH_ALEN]= {0x00,0x0c,0x29,0x15,0x61,0x80};
    char ether_dst_mac[ETH_ALEN] = {0xff,0xff,0xff,0xff,0xff,0xff};
    //char arp_src_mac[ETH_ALEN] = {0xff,0xff,0xff,0xff,0xff,0xf0};
    char arp_src_mac[ETH_ALEN] = {0x00,0x0c,0x29,0x15,0x61,0x80};
    char arp_dst_mac[ETH_ALEN] = {0xff,0xff,0xff,0xff,0xff,0xff};
   // char *ether_src_mac= "ff:ff:ff:ff:ff:f0";
   // char *ether_dst_mac = "ff:ff:ff:ff:ff:ff";
   // char *arp_src_mac = "ff:ff:ff:ff:ff:f0";
   // char *arp_dst_mac = "ff:ff:ff:ff:ff:ff";
    //char *src_ip = "192.168.157.139";
    char *src_ip = "192.168.157.138";
    char *dst_ip = "192.168.157.1";
    build_arp(buf, ether_src_mac, ether_dst_mac, arp_src_mac, arp_dst_mac, src_ip, dst_ip );
    n = sendto(skfd, buf, BUFLEN, 0, (struct sockaddr*)&toaddr, sizeof(toaddr));
    printf("n = %d\n", n);
    close(skfd);
}
void test(int argc,char** argv)
{
    int skfd,n;
    char buf[BUFLEN]={0};
    struct ether_header *eth;
    struct ether_arp *arp;
    struct sockaddr_ll toaddr;
    struct in_addr targetIP,srcIP;
    struct ifreq ifr;

    unsigned char src_mac[ETH_ALEN]={0};
    unsigned char dst_mac[ETH_ALEN]={0xff,0xff,0xff,0xff,0xff,0xff}; //全网广播ARP请求
    if(3 != argc){
            printf("Usage: %s netdevName dstIP\n",argv[0]);
            exit(1);
    }

    if(0>(skfd=socket(PF_PACKET,SOCK_RAW,htons(ETH_P_ALL)))){
            perror("Create Error");
            exit(1);
    }

    bzero(&toaddr,sizeof(toaddr));
    bzero(&ifr,sizeof(ifr));
    strcpy(ifr.ifr_name,argv[1]);

    //获取接口索引
    if(-1 == ioctl(skfd,SIOCGIFINDEX,&ifr)){
           perror("get dev index error:");
           exit(1);
    }
    toaddr.sll_ifindex = ifr.ifr_ifindex;
    printf("interface Index:%d\n",ifr.ifr_ifindex);
    //获取接口IP地址
    if(-1 == ioctl(skfd,SIOCGIFADDR,&ifr)){
           perror("get IP addr error:");
           exit(1);
    }
    srcIP.s_addr = ((struct sockaddr_in*)&(ifr.ifr_addr))->sin_addr.s_addr;
    printf("IP addr:%s\n",inet_ntoa(((struct sockaddr_in*)&(ifr.ifr_addr))->sin_addr));

    //获取接口的MAC地址
    if(-1 == ioctl(skfd,SIOCGIFHWADDR,&ifr)){
           perror("get dev MAC addr error:");
           exit(1);
    }

    memcpy(src_mac,ifr.ifr_hwaddr.sa_data,ETH_ALEN);
    printf("MAC :%02X-%02X-%02X-%02X-%02X-%02X\n",src_mac[0],src_mac[1],src_mac[2],src_mac[3],src_mac[4],src_mac[5]);


    //开始填充，构造以太头部
    eth=(struct ether_header*)buf;
    memcpy(eth->ether_dhost,dst_mac,ETH_ALEN); 
    memcpy(eth->ether_shost,src_mac,ETH_ALEN);
    eth->ether_type = htons(ETHERTYPE_ARP);

    //手动开始填充用ARP报文首部
    arp=(struct ether_arp*)(buf+sizeof(struct ether_header));
    arp->arp_hrd = htons(ARPHRD_ETHER); //硬件类型为以太
    arp->arp_pro = htons(ETHERTYPE_IP); //协议类型为IP

    //硬件地址长度和IPV4地址长度分别是6字节和4字节
    arp->arp_hln = ETH_ALEN;
    arp->arp_pln = 4;

    //操作码，这里我们发送ARP请求
    arp->arp_op = htons(ARPOP_REQUEST);
      
    //填充发送端的MAC和IP地址
    memcpy(arp->arp_sha,src_mac,ETH_ALEN);
    memcpy(arp->arp_spa,&srcIP,4);

    //填充目的端的IP地址，MAC地址不用管
    inet_pton(AF_INET,argv[2],&targetIP);
    memcpy(arp->arp_tpa,&targetIP,4);

    toaddr.sll_family = PF_PACKET;
    n=sendto(skfd,buf,BUFLEN,0,(struct sockaddr*)&toaddr,sizeof(toaddr));

    close(skfd);

}
int main(int argc,char** argv){
    //test(argc, argv);
    //send_arp();
    testm();
    return 0;
}
