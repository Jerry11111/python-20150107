#include<stdio.h>
#include<stdlib.h>
#include "queue.h"
void test()
{
	struct test{
		int a;
		SLIST_ENTRY(test) next;
	};
	static SLIST_HEAD(,test) test_head;
	struct test *p = malloc(sizeof(struct test));
	p->a = 222;
	SLIST_INSERT_HEAD(&test_head,p,next);
	SLIST_FOREACH(p,&test_head,next)
	{
		printf("%d\n",p->a);
	}
	while (!SLIST_EMPTY(&test_head)) {       /* List Deletion. */
		p = SLIST_FIRST(&test_head);
		SLIST_REMOVE_HEAD(&test_head, next);
		free(p);
	}

}
void test2()
{
	LIST_HEAD(slisthead, entry) head;
	struct slisthead *headp;        /* 单向链表头部 */
	struct entry {
		SLIST_ENTRY(entry) entries;     /* 单向链表 */
		int data;
	} *n1, *n2, *n3, *np;

	SLIST_INIT(&head);      /* 初始化链表 */

	//n1 = malloc(sizeof(struct entry));      /* 插入到头部 */
	//SLIST_INSERT_HEAD(&head, n1, entries);

	//n2 = malloc(sizeof(struct entry));      /* 插入n1后面 */
	//SLIST_INSERT_AFTER(n1, n2, entries);

	//SLIST_REMOVE(&head, n2, entry, entries);        /* 移除n2 */
	//free(n2);

	//n3 = head.slh_first;        /* 移除头部元素 */
	//SLIST_REMOVE_HEAD(&head, entries);
	//free(n3);

	//for (np = head.slh_first; np != NULL; np = np->entries.sle_next)        /* 遍历 */
	//	np->data = 1;

	//while (head.slh_first != NULL) {
	//	n1 = head.slh_first;
	//	SLIST_REMOVE_HEAD(&head, entries);
	//	free(n1);
	//}
}
int main(int argc, char **argv)
{
	test2();
	return 0;
}
