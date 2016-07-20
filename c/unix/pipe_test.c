#include "header.h"
#include <pthread.h>
#include <unistd.h>
#include <string.h>

// 父进程写, 子进程读
void pipe1()
{
	int n;
    int fd[2];
    pid_t pid;
	int MAXLINE = 100;
    char line[MAXLINE];
    if(pipe(fd)< 0){                 /* 先建立管道得到一对文件描述符 */
        exit(0);
    }
    if((pid = fork())< 0)            /* 父进程把文件描述符复制给子进程 */
        exit(1);
    else if(pid > 0){                /* 父进程写 */
        close(fd[0]);                /* 关闭读描述符 */
        write(fd[1], "\nhello world\n", 14);
    }
    else{                            /* 子进程读 */
        close(fd[1]);                /* 关闭写端 */
        n = read(fd[0], line, MAXLINE);
        write(STDOUT_FILENO, line, n);
    }
	printf("%d\n", pid);
}
// 子进程写, 父进程读
void pipe2()
{
	int n;
    int fd[2];
    pid_t pid;
	int MAXLINE = 100;
    char line[MAXLINE];
    if(pipe(fd)< 0){                 /* 先建立管道得到一对文件描述符 */
        exit(0);
    }
    if((pid = fork())< 0)            /* 父进程把文件描述符复制给子进程 */
        exit(1);
    else if(pid > 0){                /* 父进程写 */
        close(fd[1]);                /* 关闭写端 */
        n = read(fd[0], line, MAXLINE);
        write(STDOUT_FILENO, line, n);
    }
    else{                            /* 子进程读 */
        close(fd[0]);                /* 关闭读描述符 */
        write(fd[1], "\nhello world\n", 14);
    }
	printf("%d\n", pid);
}
int fork1 ()   
{   
    pid_t fpid; //fpid表示fork函数返回的值  
    int count=0;  
	printf("fork前\n");
    fpid=fork();   
    if (fpid < 0)   
        printf("error in fork!");   
    else if (fpid == 0) {  
        printf("i am the child process, my process id is %d\n",getpid());   
        printf("我是爹的儿子\n");//对某些人来说中文看着更直白。  
        count++;  
    }  
    else {  
        printf("i am the parent process, my process id is %d\n",getpid());   
        printf("我是孩子他爹\n");  
        count++;  
    }  
    printf("统计结果是: %d\n",count);  
    return 0;  
}  
int fifo_write()  
{  
	int fd;  
	char * myfifo = "/tmp/myfifo";  
	/* create the FIFO (named pipe) */  
	mkfifo(myfifo, 0666);  
	/* write "Hi" to the FIFO */  
	fd = open(myfifo, O_WRONLY);  
	write(fd, "Hi", sizeof("Hi"));  
	close(fd);  
	/* remove the FIFO */  
	//unlink(myfifo);  
	return 0;  
}
int fifo_read()  
{  
	int fd;  
	int MAX_BUF = 1024;
	char * myfifo = "/tmp/myfifo";  
	char buf[MAX_BUF];  
	/* open, read, and display the message from the FIFO */  
	fd = open(myfifo, O_RDONLY);  
	read(fd, buf, MAX_BUF);  
	printf("Received: %s\n", buf);  
	close(fd);  
	return 0;  
} 
void fifo1()
{
	pid_t fpid = 0;
	fpid = fork();
	if(fpid < 0)
	{
		perror("fork error");
		return;
	}	
    else if(fpid == 0)
    {
		fifo_read();	
	}
	else
	{
		fifo_write();	
	}
}
void * r_thread(void *arg)
{
	int fd = *((int *)arg);
	char buf[2014];
	size_t len = 0;
	printf("r_thread start\n");
	while(1)
	{
		if((len = read(fd, buf,1024)) == -1)
		{
			perror("read error");
			return;
		}
		printf("read [%s]\n", buf);
		sleep(1);
	}
}
void *  w_thread(void *arg)
{
	int fd = *((int *)arg);
	char buf[2014] = "hello world!";
	size_t len = 0;
	printf("w_thread start\n");
	while(1)
	{
		if((len = write(fd, buf,strlen(buf))) == -1)
		{
			perror("write error");
			return;
		}
		printf("write [%s]\n", buf);
		sleep(1);
	}
}
void * test_thread()
{
	printf("test thread\n");
}
void thread_pipe_test()
{
	int fd[2];
	if(pipe(fd) == -1)
	{
		perror("pipe error");
		return;
	}
	printf("%d %d\n", fd[0], fd[1]);
	pthread_t rtid, wtid, ttid;
	int rid, wid;
	if((rid = pthread_create(&rtid, NULL, r_thread, (void *)&fd[0])) != 0)
	{
		perror("create read thread error");
	}
	if((wid = pthread_create(&wtid, NULL, w_thread, (void *)&fd[1])) != 0)
	{
		perror("create write thread error");
	}
	if((wid = pthread_create(&ttid, NULL, test_thread, NULL)) != 0)
	{
		perror("create test thread error");
	}
	//printf("%d %d\n", rid, wid);
	printf("%lx %lx\n", rtid, wtid);
	sleep(10000);
	printf("end");
}
int main(int argc, char** argv)
{
	//printf("Hello World!");
	//pipe2();
	//fork1();
	//fifo1();
	thread_pipe_test();
}
