#include "header.h"

void test()
{
	int n;
    int fd[2];
    pid_t pid;
	int MAXLINE = 100;
    char line[MAXLINE];
   
    if(pipe(fd) == -1){                 /* 先建立管道得到一对文件描述符 */
		perror("pipe error");
        exit(0);
    }

    if((pid = fork()) == -1)            /* 父进程把文件描述符复制给子进程 */
	{
		perror("fork error");
        exit(1);
	}
    else if(pid > 0){                /* 父进程写 */
        close(fd[0]);                /* 关闭读描述符 */
		printf("pid(%d)send msg\n", pid);
        write(fd[1], "\nhello world\n", 14);
    }
    else{                            /* 子进程读 */
        close(fd[1]);                /* 关闭写端 */
        n = read(fd[0], line, MAXLINE);
		printf("pid(%d)receive msg\n", pid);
        write(STDOUT_FILENO, line, n);
    }

    exit(0);	
}
int main(int argc, char** argv)
{

	test();
	return 0;
}
