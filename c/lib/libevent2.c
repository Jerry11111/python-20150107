#include <stdio.h>
#include <stdlib.h>
#include <event2/event.h>
#include <event.h>

int main(int argc, char **argv)
{
	struct event_base *base = event_base_new();
	//printf("%ld\n", sizeof(struct event_base));
	//printf("%d\n", base->event_count);
	printf("hello world!");
	return 0;
}
