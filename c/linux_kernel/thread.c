#include "header.h"
#include <pthread.h>
#include <errno.h>
#include <stdlib.h>
void printids(const char *s)
{
	pid_t  pid;
	pthread_t  tid;
	pid = getpid();
	tid = pthread_self();
	printf("%s pid %lu tid %lu (0x%lx)\n", s, (unsigned long)pid,
	(unsigned long)tid, (unsigned long)tid);
}
void thread1(void *arg)
{
	printids("new thread: ");
	sleep(100);
	//pthread_exit(0);
}
void * thread2(void *arg)
{
	int d = *((int *)arg);
	printf("d = %d\n", d);
	printids("new thread: ");
	sleep(100);
	//pthread_exit(0);
}
void create_thread()
{
	int  p1;
	pthread_t ntid;
	p1 = pthread_create(&ntid, NULL, (void *)thread1, NULL);
	if (p1 != 0)
		perror("can’t create thread");
	int d = 1;
	if(pthread_create(&ntid, NULL, thread2, &d) !=0)
	{
		perror("create thread2 error");
	}
	printids("main thread:");
	sleep(100);
}
int main(int argc, char **argv)
{
	//thread_lock();
	//pthread_mutex_test2();
	create_thread();
	return 0;
}
