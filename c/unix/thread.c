#include "header.h"
#include <pthread.h>
#include <errno.h>
#include<stdlib.h>
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
	//pthread_exit(0);
}
void create_thread()
{
	int  err;
	pthread_t ntid;
	err = pthread_create(&ntid, NULL, (void *)thread1, NULL);
	if (err != 0)
		perror("can’t create thread");
	printids("main thread:");
	sleep(1);
}
void * thr_fn1(void *arg)
{
	printf("thread 1 returning\n");
	return((void *)1);
}
void * thr_fn2(void *arg)
{
	printf("thread 2 exiting\n");
	pthread_exit((void *)2);
}

void join_thread()
{
	int  err;
	pthread_t  tid1, tid2;
	void  *tret;
	err = pthread_create(&tid1, NULL, thr_fn1, NULL);
	if (err != 0)
		perror("can’t create thread 1");
	err = pthread_create(&tid2, NULL, thr_fn2, NULL);
	if (err != 0)
		perror("can’t create thread 2");
	err = pthread_join(tid1, &tret);
	if (err != 0)
		perror("can’t join with thread 1");
	printf("thread 1 exit code %ld\n", (long)tret);
	err = pthread_join(tid2, &tret);
	if (err != 0)
		perror("can’t join with thread 2");
	printf("thread 2 exit code %ld\n", (long)tret);
}
void thread_lock()
{
	extern int err;
	struct timespec tout;
	struct tm *tmp;
	char buf[64];
	pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_lock(&lock);
	printf("mutex is locked\n");
	clock_gettime(CLOCK_REALTIME, &tout);
	tmp = localtime(&tout.tv_sec);
	strftime(buf, sizeof(buf), "%r", tmp);
	printf("current time is %s\n", buf);
	tout.tv_sec += 10; /* 10 seconds from now */
	/* caution: this could lead to deadlock */
	err = pthread_mutex_timedlock(&lock, &tout);
	clock_gettime(CLOCK_REALTIME, &tout);
	tmp = localtime(&tout.tv_sec);
	strftime(buf, sizeof(buf), "%r", tmp);
	printf("the time is now %s\n", buf);
	//char *msg = strerror(err);
	if (err == 0)
		printf("mutex locked again!\n");
	else
		//printf("can’t lock mutex again: %s\n", msg);
		printf("can’t lock mutex again: %d\n", err);
}
int main(int argc, char **argv)
{
	thread_lock();
	return 0;
}
