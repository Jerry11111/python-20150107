#include<stdio.h>
#include<stdlib.h>

void test1()
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

}
int bss_var;
int data_var0 = 1;
int main(int argc, char **argv)
{
	//int i = 1;
	//printf("%p %p\n", main, &i);
	printf("Test location:\n");
	printf("\tAddress of main(Code Segment):%p\n",main);
	printf("_____________________________________\n");
	int stack_var0 = 2;
	printf("Stack location:\n");
	printf("\tInitial end of stack:%p\n",&stack_var0);
	int stack_var1 = 3;
	printf("\tNew end of stack:%p\n",&stack_var1);
	printf("_____________________________________\n");
	printf("Data location:\n");
	printf("\tAddress of data_var(Data Segment):%p\n",&data_var0);
	static int data_var1 = 4;
	printf("\tNew end of data_var(Data Segment):%p\n",&data_var1);
	 printf("_____________________________________\n");
	printf("BSS location:\n");
	printf("\tAddress of bss_var:%p\n",&bss_var);
	printf("_____________________________________\n");
	 printf("Heap location:\n");
	char *p = (char *)malloc(10);
	printf("\tAddress of head_var:%p\n",p);
	return 0;
}
