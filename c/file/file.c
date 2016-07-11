#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "header.h"
#include <dirent.h>
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
// 向文件中写入空,生成空洞文件
void test_lseek2()
{
	int fd;  
    char buf1[100] = "";  
	//bzero(buf1,sizeof(buf1)); 
    if((fd = open("h",O_CREAT|O_RDWR)) < 0)  
        perror("open error\n");  
    if(write(fd,buf1,sizeof(buf1)) > 0)  
        perror("buf1 write error\n");  
}
void test_open()
{
	int fd;  
    char buf1[100] = "";  
	//bzero(buf1,sizeof(buf1)); 
	// 指定属主队文件的操作权限,默认为只读权限
    if((fd = open("open_file.txt",O_CREAT|O_RDWR, S_IRUSR | S_IWUSR | S_IXUSR)) < 0)  
        perror("open error\n");  
}
void test_fcntl()
{
	int fd = -1;
	char path[]= "ip.txt";
	if((fd = open(path, O_CREAT|O_RDWR|O_APPEND)) == -1)
	{
		perror("open error");
		exit(1);
	}
	int val = -1;
	if((val = fcntl(fd, F_GETFL, 0)) < 0)
	{
		perror("fcntl error");
	}
	printf("fd=%d, val=%d\n", fd, val);
	// 文件的访问模式
	switch(val & O_ACCMODE)
	{
		case O_RDONLY:
			printf("read only");
			break;
		case O_WRONLY:
			printf("write only");
			break;
		case O_RDWR:
			printf("read write");
			break;
		default:
			printf("unknown access mode");
	}
	if(val & O_APPEND)
	{
		printf(", append");
	}
}
// dup复制文件描述,两个文件描述符的信息完全相同
void test_dup()
{
	int fd = -1;
	char path[]="ip.txt";
	if(( fd = open(path, O_RDWR)) == -1)
	{
		perror("open error");
		exit(1);
	}
	int cp_fd = -1;
	cp_fd = dup(fd);
	printf("fd=%d, cp_fd=%d\n", fd, cp_fd);
	char buf1[] = "hello ";
    char buf2[] = "world!";
 
    //往fd文件写入内容
    if (write(fd, buf1, 6) != 6) {
        perror("write error!");
    }
 
    //打印出fd和copyfd的偏移量，经过上面的写操作，都变成6了
    printf("fd.cur=%d\n", (int)lseek(fd, 0, SEEK_CUR));
    printf("cp_fd.cur=%d\n", (int)lseek(cp_fd, 0, SEEK_CUR));
 
    //往copyfd写入内容
    if (write(cp_fd, buf2, 6) != 6) {
        perror("write error!");
    }
	char buf3[100]="";
	if(read(fd, buf3, sizeof(buf3)) == -1)
	{
		perror("read error");
	}
	printf("buf3=%s\n", buf3);
}
void test_lseek3()
{
	if(lseek(STDIN_FILENO, 0, SEEK_CUR) == -1)
	{
		printf("can not seek\n");
	}
	else
	{
		printf("seek ok\n");
	}
	char buf[1000] = "";
	// 从标准输入读取
	if(read(STDIN_FILENO, buf, sizeof(buf)) == -1)
	{
		perror("read error");	
		exit(1);
	}
	printf("buf=%s\n", buf);
}
void copy_file()
{
	int  n;
	char  buf[1024];
	while ((n = read(STDIN_FILENO, buf, 1024)) > 0)
	if (write(STDOUT_FILENO, buf, n) != n)
	{
		printf("write error");
	}
	if (n < 0)
	{
		printf("read error");	
	}
}
// 目录操作
void dir_test()
{
	DIR    *dir;
    struct    dirent    *ptr;
    dir = opendir("."); ///open the dir

    while((ptr = readdir(dir)) != NULL) ///read the list of this dir
    {
       printf("d_type:%d d_name: %s\n", ptr->d_type,ptr->d_name);
    }
    closedir(dir);	
}
int main(int argc, char **argv)
{
	//test_lseek2();
	dir_test();
	return 0;
}

