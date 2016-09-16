#include<stdio.h>
#include<stdlib.h>

int main(int argc, char **argv)
{
	printf("Hello World!\n");
	struct list_head{
		struct list_head *next, *prev;
	};
	struct file_node{
		char c;
		struct list_head node;
	};
	#define offsetof(TYPE,MEMBER) ( (size_t)& ((TYPE *)0)-> MEMBER )
	size_t s = offsetof(struct file_node, node);
	printf("%ld\n", s);
	return 0;
}
