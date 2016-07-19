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
	#define SLIST_INSERT_HEAD(head, elm, field) do {	\
		elm->field.sle_next = head->slh_first;	\
		head->slh_first = elm;	\
    } while(0)
	#define SLIST_INSERT_AFTER(slistelm, elm, field) do {	\
		(elm)->field.sle_next = (slistelm)->field.sle_next;	\
		(slistelm)->field.sle_next = (elm);	\
	} while(0)

	struct test{
		int data;
		SLIST_ENTRY(test) next;
	};
	SLIST_HEAD(,test) test_head;
	//bzero(&test_head, sizeof(test_head));
	//printf("%d %p\n", (&test_head)->slh_first->data, (&test_head)->slh_first->next);
	//printf("%d\n", (&test_head)->slh_first->data);
	struct test *p = malloc(sizeof(struct test));
	p->data = 1;
	struct test *p2 = malloc(sizeof(struct test));
	p2->data = 2;
	//p->next.sle_next = p2;
	SLIST_INSERT_AFTER(p, p2, next);
	printf("%d %d\n", p->data, (p->next).sle_next->data);
	return 0;
}
