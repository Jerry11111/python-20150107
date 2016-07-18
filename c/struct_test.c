#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char **argv)
{
	#define SLIST_HEAD(name, type)	\
	struct name{ 	\
		struct type *slh_first;	\
	}
	#define SLIST_ENTRY(type)	\
	struct{	\
		struct type *sle_next;	\
	}
	struct test{
		int data;
		SLIST_ENTRY(test) next;
	};
	SLIST_HEAD(,test) test_head;
	//bzero(&test_head, sizeof(test_head));
	//printf("%d %p\n", (&test_head)->slh_first->data, (&test_head)->slh_first->next);
	//printf("%d\n", (&test_head)->slh_first->data);
	struct test *p = malloc(sizeof(struct test));
	printf("%d\n", p->data);
	return 0;
}
