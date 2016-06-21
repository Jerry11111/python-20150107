#include "header.h"

void read_file()
{
	FILE *f = fopen("ip.txt", "r");	
	if( f == NULL)
	{
		perror("open file error");
		exit(0);
	}
	char buf[1000] = "";
	char* res = fgets(buf, 1000, f);
	if(res == NULL)
	{
		perror("read file error");
		exit(0);
	}
	int r = fclose(f);
	if(r < 0)
	{
		perror("close file error");
		exit(0);
	}
	printf("%s\n", buf);
}
void test_rw_char()
{
	int  c;
	// getc,putc 读取输入到输入
	while ((c = getc(stdin)) != EOF)
	{
		if (putc(c, stdout) == EOF)
		{
			perror("output error");
		}
	}
	if (ferror(stdin))
		perror("input error");
}
void  test_rw_char2()
{
	// fgets,fputc 读取输入到输入
	int MAXLINE = 1024;
	char  buf[MAXLINE];
	while (fgets(buf, MAXLINE, stdin) != NULL)
	{
		if (fputs(buf, stdout) == EOF)
		perror("output error");
	}
	if (ferror(stdin))
	{
		perror("input error");
	}
}
void test_temp_file()
{
	// tempname, tempfile函数用来创建临时文件
	int MAXLINE = 1024;
	char  name[MAXLINE], line[MAXLINE];
	FILE  *fp;
	printf("tmpnam(NULL)=>%s\n", tmpnam(NULL)); /* first temp name */
	tmpnam(name);  /* second temp name */
	printf("tmpnam(name)=>%s\n", name);
	if ((fp = tmpfile()) == NULL) /* create temp file */
	perror("tmpfile error");
	fputs("one line of output\n", fp); /* write to temp file */
	rewind(fp);  /* then read it back */
	if (fgets(line, sizeof(line), fp) == NULL)
	perror("fgets error");
	fputs(line, stdout); /* print the line we wrote */
	// 创建临时文件
	int fd = -1;
	char temp_dir[] = "/tmp/dirXXXXXX";
	if((fd = mkstemp(temp_dir)) < 0)
	{
		perror("create temp dir error");
	}
	close(fd);
	struct stat sbuf;
	if (stat(temp_dir, &sbuf) < 0) {
		if (errno == ENOENT)
			printf("file doesn’t exist\n");
		else
			printf("stat failed");
	} else {
		printf("file exists\n");
		unlink(temp_dir);
	}
	// 创建临时目录
	char temp_d[] = "/tmp/dirXXXXXX";
	if(mkdtemp(temp_d) == NULL)
	{
		perror("mkdtemp error");
	}
	printf("temp dir: %s\n", temp_d);
	exit(0);
}
int main(int argc, char **argv)
{
	read_file();
	return 0;
}
