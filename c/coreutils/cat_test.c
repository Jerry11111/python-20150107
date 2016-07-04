#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
int main(int argc, char **argv)
{
	int opt;
	char *optstring = "n";
	int i = 0;
	for(i = 0; i < argc; i++)
	{
	//	printf("[%d] [%s]\n", i, argv[i]);

	}
	int argind;
	int number = 0;
	while((opt = getopt(argc, argv, optstring)) != -1)
	{
		switch(opt)
		{
			case 'n':
				number = 1;
				break;
			default:
				;
				
		}
		//printf("[%c] [%d] [%s]\n", opt, optind, argv[optind]);
	}
	argind = optind;
	char *infile = argv[argind];
	FILE *infp;
	char *line = NULL;
	size_t linesize = 0;
	size_t read = 0;
	if((infp = fopen(infile, "r")) == NULL)
	{
		perror("open file error");
		exit(1);
	}
	size_t n= 0;
	while((read = getline(&line, &linesize,infp)) != -1)
	{
		if(number > 0)
		{
			size_t newsize = linesize + 10;
			char *newline = malloc(newsize);
			bzero(newline, newsize);
			char tmp[10];
			sprintf(tmp, "\t%zu\t", ++n);
			strcat(newline, tmp);
			strcat(newline, line);
			line = newline;
		}
		if(fputs(line, stdout) < 0)
		{
			perror("write error");
			exit(1);
		}

	}
	fclose(infp);
}

