#include "header.h"
#include <fcntl.h>
#include <errno.h>
#include <string.h>

void set_fl(int fd, int flags)
{
    int        val;

    if ( (val = fcntl(fd, F_GETFL, 0)) < 0)
        {
            printf("fcntl F_GETFL error");
            exit(1);
        }

    val |= flags;       

    if (fcntl(fd, F_SETFL, val) < 0)
        {
            printf("fcntl F_SETFL error");
            exit(1);
        }
}

void clr_fl(int fd, int flags)
{
    int val;

    if ((val = fcntl(fd, F_GETFL, 0)) == -1)
    {
		perror("fcntl error");
        exit(1);
    }
    val &= ~flags;

    if (fcntl(fd, F_SETFL, val) == -1)
    {
		perror("fcntl error");
        exit(1);
    }
    return;
}
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
void test()
{
	char  buf[500000];
	int  ntowrite, nwrite;
	char  *ptr;
	ntowrite = read(STDIN_FILENO, buf, sizeof(buf));
	fprintf(stderr, "read %d bytes\n", ntowrite);
	set_fl(STDOUT_FILENO, O_NONBLOCK); /* set nonblocking */
	ptr = buf;
	while (ntowrite > 0) 
	{
		errno = 0;
		nwrite = write(STDOUT_FILENO, ptr, ntowrite);
		fprintf(stderr, "nwrite = %d, errno = %d\n", nwrite, errno);
		if (nwrite > 0) 
		{
			ptr += nwrite;
			ntowrite -= nwrite;
		}
	}
	clr_fl(STDOUT_FILENO, O_NONBLOCK); /* clear nonblocking */	
}
void test_lock()
{
	int fd;
	char path[]="ip.txt";
	//if((fd = open(path, O_RDONLY | O_WRONLY) == -1))
	if((fd = open(path, O_RDONLY)) == -1)
	{
		perror("open file error");	
		exit(1);
	}
	printf("fd=%d\n", fd);
	struct flock lock;
	lock.l_type = F_RDLCK; /* F_RDLCK, F_WRLCK, F_UNLCK */
	lock.l_start = 0; /* byte offset, relative to l_whence */
	lock.l_whence = SEEK_SET; /* SEEK_SET, SEEK_CUR, SEEK_END */
	lock.l_len = 0; /* #bytes (0 means to EOF) */
	int r = -1;
	if((r = fcntl(fd, F_SETLK, &lock)) == -1)
	{
		perror("fcntl error");	
		exit(1);
	}
	//printf("fd=%d, r=%d\n", fd, r);
	printf("lock file: l_type=%d, l_start=%ld, l_whence=%d, l_len=%ld\n", lock.l_type, lock.l_start, lock.l_whence, lock.l_len);
	sleep(1000);
	
}
void test_lock_status()
{
	char path[]="ip.txt";
	// 查看文件锁
	int r2 = -1;
	struct flock lock2;
	bzero(&lock2, sizeof(lock2));
	int fd2 = -1;
	if((fd2 = open(path, O_RDONLY)) == -1)
	{
		perror("open file error");	
		exit(1);
	}
	//printf("fd2=%d\n", fd2);
	if((r2 = fcntl(fd2, F_GETLK, &lock2)) == -1)
	{
		perror("fcntl error");	
		exit(1);
	}
	printf("lock file status: l_type=%d, l_start=%ld, l_whence=%d, l_len=%ld\n", lock2.l_type, lock2.l_start, lock2.l_whence, lock2.l_len);
	
}
int main(int argc, char **argv)
{
	test_lock();
	return 0;
}
