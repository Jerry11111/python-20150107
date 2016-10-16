#define _GNU_SOURCE       /* or _BSD_SOURCE or _SVID_SOURCE */
#include <unistd.h>
#include <sys/syscall.h> /* For SYS_xxx definitions */
#include <sys/types.h>
#include <sched.h>
#include <sys/mman.h>
#include <signal.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
void test_fork()
{
	printf("hello world!");
	pid_t pid;
	printf("fork!\n");
	// fork 返回0表示为子进程, 大于0表示符进程
	if((pid = fork()) < 0){
		printf("fork error\n");
	}else if(pid == 0){
		pid_t spid = getpid();
		printf("[child process] [%d]\n", spid);
		sleep(100);
	}else{
		pid_t ppid = getpid();
		printf("[parent process] [%d %d]\n", ppid, pid);
		printf("test\n");
		wait(NULL);
		printf("Child Complete!\n");
	}

}
#define STACK_SIZE 1024*1024*8 //8M

int thread_func(void *args)
{
    printf("thread id %d \n", (int)syscall(SYS_gettid));
	pid_t pid = getpid();
	printf("[son] [%d]", pid);
    sleep(1);
    return 0;
}
void test_clone()
{
    void *pstack = (void *)mmap(NULL,
                                STACK_SIZE,
                                PROT_READ | PROT_WRITE ,
                              MAP_PRIVATE | MAP_ANONYMOUS | MAP_ANON ,//| MAP_GROWSDOWN ,
                                -1,
                                0);
    if (MAP_FAILED == pstack){
		printf("mmap error\n");
		exit(-1);
    }

	int ret;
	printf("strace addr : 0x%p\n", pstack);
	/*
	CLONE_VM (0x100) - tells the kernel to let the original process and 
						the clone in the same memory space;
	CLONE_FS (0x200) - both get the same file system information;
	CLONE_FILES (0x400) - share file descriptors;
	CLONE_SIGHAND (0x800) - both processes share the same signal handlers;
	CLONE_THREAD (0x10000) - this tells the kernel, that both processes would belong
					 to the same thread group (be threads within the same process);
	*/
	ret = clone(thread_func,
				(void *)((unsigned char *)pstack + STACK_SIZE),
				CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND |SIGCHLD,
				(void *)NULL);
    if( ret == -1){
		printf("clone error\n");
        exit(-1);
    }
	pid_t pid = getpid();
	printf("[parent] [%d %d]\n", pid, ret);
	printf("start thread %d \n", ret);
	sleep(5);
	
}
int main(int argc, char **argv)
{
	test_clone();
	return 0;
}
