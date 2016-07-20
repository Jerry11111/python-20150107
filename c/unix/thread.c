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
	//pthread_exit(0);
}
void * thread2(void *arg)
{
	int d = *((int *)arg);
	printf("d = %d\n", d);
	printids("new thread: ");
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
pthread_mutex_t mutex ;  
void *print_msg(void *arg){  
	int i=0;  
	pthread_mutex_lock(&mutex);  
	pthread_t tid = pthread_self(); 
	for(i=0;i<15;i++){  
			printf("[%lx] %d\n",(unsigned long)tid, i);  
			usleep(100);  
	}  
	pthread_mutex_unlock(&mutex);  
}  
void pthread_mutex_test(){  
	pthread_t id1;  
	pthread_t id2;  
	pthread_mutex_init(&mutex,NULL);  
	pthread_create(&id1,NULL,print_msg,NULL);  
	pthread_create(&id2,NULL,print_msg,NULL);  
	pthread_join(id1,NULL);  
	pthread_join(id2,NULL);  
	pthread_mutex_destroy(&mutex);  
}
void *print_msg2(void *arg){  
	int i=0;  
	pthread_t tid = pthread_self(); 
	for(i=0;i<15;i++){  
			printf("[%lx] %d\n",(unsigned long)tid, i);  
			usleep(100);  
	}  
}  
void pthread_mutex_test2(){  
	pthread_t id1;  
	pthread_t id2;  
	pthread_create(&id1,NULL,print_msg2,NULL);  
	pthread_create(&id2,NULL,print_msg2,NULL);  
	pthread_join(id1,NULL);  
	pthread_join(id2,NULL);  
}
int main(int argc, char **argv)
{
	//thread_lock();
	//pthread_mutex_test2();
	create_thread();
	return 0;
}
