#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>

void test_strerror()
{
	FILE*fp;
	extern int errno;
	char *message;
	if(NULL==(fp=fopen("/dev/dsp","r+")))
	{
		printf("errno=%d\n",errno);
		message = strerror(errno);
		printf("Mesg:%s\n",message);
		perror("perror");
	}
	exit(0);	
}
int main(int argc, char **argv)
{
	test_strerror();
	return 0;
}
