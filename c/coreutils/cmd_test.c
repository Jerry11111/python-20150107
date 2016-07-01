#include<stdio.h>
#include <unistd.h>
#include <fcntl.h>
int main(int argc, char **argv)
{
	int opt;
	char *optstring = "abcdef";
	printf("%d\n", argc);
	int i = 0;
	for(i = 0; i < argc; i++)
	{
		printf("[%d] [%s]\n", i, argv[i]);

	}
	int argind;
	while((opt = getopt(argc, argv, optstring)) != -1)
	{
		//switch(opt)
		//{
		//	case 'a':
		//		
		//}
		printf("[%c] [%d] [%s]\n", opt, optind, argv[optind]);
	}
	argind = optind;
	char *infile = argv[argind];
	int infd;
	if((infd = open(infile, O_RDONLY)) == -1)
	{
		perror("open file error");	
	}
	size_t bufsize = 4096;
	size_t len;
	char buf[bufsize];
	while(1)
	{
		if(( len = read(infd, buf, bufsize)) < 0)
		{
			perror("read error");
			break;
		}
		if(len == 0)
		{
			break;
		}
		if( write(1, buf, len) != len)
		{
			perror("write error");
			break;
		}
	}
}

