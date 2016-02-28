#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "header.h"
void read_file()
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
	if(close(fd) == -1)
	{
		perror("close file error");
		exit(1);
	}
	printf("%s", buf);

}
// 分多次读取一个文件
void read_file2()
{
	int fd = 0;
	fd = open("ip.txt", O_RDONLY);
	if(fd == -1)
	{
		perror("open file error");
		exit(1);
	}
	char buf[10000] = "";
	char a[10000] = "";
	char *p = a;
	int buf_len = 10;
	ssize_t read_len = 0;
	while((read_len = read(fd, buf, buf_len)) > 0)
	{
		//printf("%s", buf);
		//bzero(buf, sizeof(buf));
		append(p, buf, 0, read_len);
	}
	printf("%s", p);

}
ssize_t read_file_as_string(char *path, char *content)
{
	int fd = 0;
	fd = open(path, O_RDONLY);
	if(fd == -1)
	{
		perror("open file error");
		return -1;
	}
	int buf_len = 4096;
	char buf[4096] = "";
	ssize_t read_len = 0;
	ssize_t total_len = 0;
	while((read_len = read(fd, buf, buf_len)) > 0)
	{
		append(content, buf, 0, read_len);
		total_len += read_len; 
	}
	if(close(fd) == -1)
	{
		perror("close file error");
		return -1;
	}
	return total_len;
}
void test_read_file_as_string()
{
	char path[] = "ip.txt";
	char content[1000]= "";
	int r = read_file_as_string(path, content); 
	printf("r=%d, content=%s\n", r, content);
}

ssize_t write_file(char *path, char *content, size_t len)
{
	int fd = 0;
	fd = open(path, O_WRONLY | O_CREAT);
	if(fd == -1)
	{
		perror("open file error");
		return -1;
	}
	int buf_len = 4096;
	char buf[4096] = "";
	ssize_t read_len = 0;
	ssize_t total_len = 0;
	total_len = write(fd, content, len);
	if(close(fd) == -1)
	{
		perror("close file error");
		return -1;
	}
	return total_len;
}
void test_write_file()
{
	char path[] = "test.txt";
	char content[1000]= "test iddss  dkkdlskdkddkdkd";
	int r = write_file(path, content, sizeof(content)); 
	printf("r=%d, content=%s\n", r, content);
}
void test_lseek()
{
	int fd;  
    char buf1[] = "abcdefghij";  
    char buf2[] = "ABCDEFGHIJ"; 
    if((fd = creat("file.hole",O_CREAT|O_RDWR)) < 0)  
        perror("creat error\n");  
    if(write(fd,buf1,10) != 10)  
        perror("buf1 write error\n");  
    if(lseek(fd,16384,SEEK_SET) == -1)  
        perror("lseek error\n");  
    if(write(fd,buf2,10) != 10)  
        perror("write buf2 error\n");  
      
    if(fd)  
        close(fd);  
}
int main(int argc, char **argv)
{
	//read_file2();
	//test_read_file_as_string();
//	test_write_file();
	test_lseek();
}

