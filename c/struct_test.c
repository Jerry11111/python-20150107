#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void slist_test()
{



}
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
		(elm)->field.sle_next = (head)->slh_first;	\
		(head)->slh_first = elm;	\
    } while(0)
	#define SLIST_INSERT_AFTER(slistelm, elm, field) do {	\
		(elm)->field.sle_next = (slistelm)->field.sle_next;	\
		(slistelm)->field.sle_next = (elm);	\
	} while(0)
	#define LIST_REMOVE_HEAD(head, field) do {	\
		(head)->slh_first = (head)->slh_first.field->sle_next;	\
	} while(0)
	#define SLIST_FIRST(head) ((head)->slh_first)
	#define SLIST_END(head) NULL
	#define SLIST_NEXT(elm, field) ((elm)->field.sle_next)
	#define SLIST_FOREACH(var, head, field)	\
		for((var) = SLIST_FIRST(head);	\
			(var) != SLIST_END(head);	\
			(var) = SLIST_NEXT(var, field))

	struct entry{
		int data;
		SLIST_ENTRY(entry) next;
	};
	SLIST_HEAD(,entry) head;// 定义head
	bzero(&head, sizeof(head));// head初始化
	//printf("%d %p\n", (&head)->slh_first->data, (&head)->slh_first->next);
	//printf("%d\n", (&head)->slh_first->data);
	struct entry *p = malloc(sizeof(struct entry));
	p->data = 1;
	struct entry *p2 = malloc(sizeof(struct entry));
	p2->data = 2;
	//p->next.sle_next = p2;
	SLIST_INSERT_HEAD(&head, p, next);
	SLIST_INSERT_AFTER(p, p2, next);
	//printf("%d %d\n", p->data, (p->next).sle_next->data);
	printf("%d %d %d\n", (&head)->slh_first->data, p->data, (p->next).sle_next->data);
	struct entry *v = NULL;
	SLIST_FOREACH(v, &head, next)
	{
		printf("%d\n", v->data);
	}
	return 0;
}
