#include<stdio.h>
// argc表示参数总数, argv表示参数字符串, argv[0]表示程序名本身
int main(int argc, char *argv[])
{
	printf("argc=%d, argv0=%s", argc, argv[0]);
}
