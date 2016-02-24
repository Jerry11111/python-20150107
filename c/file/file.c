#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
int main(int argc, char **argv)
{
	int fd = 0;
	fd = open("ip.txt", O_RDONLY);
	if(fd == -1)
	{
		perror("open file error");
		exit(1);
	}
	char buf[10000] = "";
	ssize_t read_len = read(fd, buf, 10000);
	if( read_len == -1)
	{
		perror("read file error");
		exit(1);
	}
	printf("%s", buf);

}

