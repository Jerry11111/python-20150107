#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include "header.h"
void test_file_type(int argc, char **argv)
{
	int i;
	struct stat buf;
	char *ptr;
	for(i = 1; i < argc; i++)
	{
		printf("%s:", argv[i]);
		if(lstat(argv[i], &buf) < 0)
		{
			perror("lstat error");
			continue;
		}
		if(S_ISREG(buf.st_mode))
		{
			ptr = "regular";
		}
		else if(S_ISDIR(buf.st_mode))
		{
			ptr = "directory";
		}
		else if(S_ISCHR(buf.st_mode))
		{
			ptr = "character special";
		}
		else if(S_ISBLK(buf.st_mode))
		{
			ptr = "block special";
		}
		else if(S_ISFIFO(buf.st_mode))
		{
			ptr = "fifo";
		}
		else if(S_ISLNK(buf.st_mode))
		{
			ptr = "symbolic link";
		}
		else if(S_ISSOCK(buf.st_mode))
		{
			ptr = "sock";
		}
		else
		{
			ptr = "** unknown mode **";
		}
		printf("%s\n", ptr);
	}

}
// 列举目录下的所有文件
void test_list_file(int argc, char **argv)
{
	DIR  *dp;
	struct dirent *dirp;
	if (argc != 2)
	{
		printf("usage: ls directory_name");
		exit(1);
	}
	printf("argc=%d\n", argc);
	printf("argv[1]=%s", argv[1]);
	if ((dp = opendir(argv[1])) == NULL)
	{
		printf("can’t open %s", argv[1]);
		exit(1);
	}
	while ((dirp = readdir(dp)) != NULL)
	{
		printf("%s\n", dirp->d_name);
	}
	closedir(dp);	
}
int main(int argc, char **argv)
{
	test_list_file(argc, argv);
	return 0;
}
