#include<stdio.h>
#include<string.h>
#include <malloc.h>

int strcat_test()
{
	char *str = "Link encap:Ethernet  HWaddr 00:0c:29:15:61:80\n";
	size_t newsize = strlen(str) + 10;
	char *newstr = malloc(newsize);
	bzero(newstr, newsize);
	char nu[10];
	// 拼接字符串 使用sprintf
	sprintf(nu, "%d ", 1);
	printf("[%s]\n", nu);
	strcat(newstr, nu);
	strcat(newstr, str);
	strcat(newstr, "test");
	printf("[%s] [%s]\n", str, newstr);
	return 0;
}
int main(int argc, char **argv)
{
	strcat_test();
	return 0;
}
