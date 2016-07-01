#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
char * skip_str(char *buf)
{
	int i = 0;
	while(*(buf + i) != '\0'){
	    i++;
	}
	return buf + i + 1;
}
void test()
{
	char *str = "abcd\0efg1234";
	char *str2 = skip_str(str);
	printf("str: %s\n", str);
	printf("str2: %s\n", str2);
  
}

void test2()
{
	long curr_secs = time(NULL);
	printf("curr_secs: %ld\n", curr_secs);
	//uint8_t t :2 = 1;
	//printf("t: %d", t);
	char *str = "abcd\0efg1234";
	char *str2 = str;
	char *str3 = "";
	printf("str: %s\n", str);
	int i = 0;
	while(*(str + i) != '\0'){
	    i++;
	}
	str3 = str + i + 1;
	printf("str2: %s\n", str2);
	printf("str3: %s\n", str3);

}
// int clock_gettime(clockid_t clk_id, struct timespec *tp);
// 用于计算精度和纳秒
void test_clock_gettime()
{
	struct timespec time1 = {0, 0};   
    clock_gettime(CLOCK_REALTIME, &time1);        
    printf("CLOCK_REALTIME: %ld, %ld\n", time1.tv_sec, time1.tv_nsec);  
    clock_gettime(CLOCK_MONOTONIC, &time1);        
    printf("CLOCK_MONOTONIC: %ld, %ld\n", time1.tv_sec, time1.tv_nsec);    
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);        
    printf("CLOCK_PROCESS_CPUTIME_ID: %ld, %ld\n", time1.tv_sec, time1.tv_nsec);   
    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &time1);        
    printf("CLOCK_THREAD_CPUTIME_ID: %ld, %ld\n", time1.tv_sec, time1.tv_nsec);   
    printf("\n%ld\n", time(NULL)); 
    sleep(5);
}
void test_localtime()
{
	time_t timer;//time_t就是long int 类型
	struct tm *t;
	timer = time(NULL);
	t= localtime(&timer);
	printf("Local time is: %s\n",asctime(t));	
	printf("%4d年%02d月%02d日 %02d:%02d:%02d\n",t->tm_year+1900,t->tm_mon+1,t->tm_mday,t->tm_hour,t->tm_min,t->tm_sec);
}
void test_strftime()
{
	time_t rawtime;
	struct tm* timeinfo;
	char timE[80];
	time(&rawtime);
	timeinfo=localtime(&rawtime);
	strftime(timE,80,"Date:\n%Y-%m-%d\nTime:\n%I:%M:%S\n",timeinfo);
	printf("%s",timE);
}
// nt gettimeofday(struct timeval*tv, struct timezone *tz);
// 用于计算精度和微秒
void test_gettimeofday()
{
	struct timeval tv_begin;
	gettimeofday(&tv_begin, NULL);
	printf("tv_sec=%ld, tv_usec=%ld\n", tv_begin.tv_sec, tv_begin.tv_usec);
}
int main(int argc,char* argv[])
{
	test_gettimeofday();
	return 0;

}
