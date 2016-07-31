#include <stdio.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <netinet/in.h>
#include <arpa/inet.h>      
#include <netdb.h> 
// libevent头文件 
#include <event.h> 
// 定时事件回调函数 
void onTime(int sock, short event, void*arg) 
{ 
	printf("Game Over!\n");
    struct timeval tv; 
    tv.tv_sec = 1; 
    tv.tv_usec = 0; 
    // 重新添加定时事件（定时事件触发后默认自动删除） 
    event_add((struct event*)arg, &tv); 
} 
void timer()
{
    // 初始化 
    event_init(); 
    struct event evTime; 
    // 设置定时事件 
    evtimer_set(&evTime, onTime, &evTime); 
    struct timeval tv; 
    tv.tv_sec = 1; 
    tv.tv_usec = 0; 
    // 添加定时事件 
    event_add(&evTime, &tv); 
    // 事件循环 
    event_dispatch(); 
}
void cb_func(int fd, short what, void *arg)
{
	const char *data = arg;
	printf("%d %d %s\n", fd, what, data);
}
void test()
{
	//struct event_base *base = event_base_new();
	//printf("%d\n", base->event_break);
	//printf("%ld\n", sizeof(int));	
	//event_base_dispatch(base);
	event_init();
	struct event *ev1;
	event_set(ev1, -1, 0, cb_func, (char *)"hello world");
	struct timeval five_seconds = {5,0};
	event_add(ev1, &five_seconds);
	//event_base_loop(base, 0x04);
	event_dispatch();
	printf("over");
}
int main(int argc, char **argv) 
{ 
	//timer();
	test();
    return 0; 
}
