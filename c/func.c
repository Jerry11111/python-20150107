#include<stdio.h>
#include<stdlib.h>

typedef int (*FuncType)(int, int);
int add(int a, int b)
{
	return a + b;
}

int op(FuncType f, int a, int b)
{
	return f(a, b);
}
void test_op()
{
	int a = op(add, 1, 2);
	printf("%d\n", a);
}
int int_add(int a, int b) { return (a+b); }
int int_sub(int a, int b) { return (a-b); }
void test_operator()
{
	int (*int_operator)(int, int) = int_add;
	int i = 0;
	i = int_operator(4, 5);
	printf("%d\n", i);
	int_operator = int_sub;
	i = int_operator(4, 5);
	printf("%d\n", i);
}
int main(int argc, char **argv)
{
	test_operator();
	return 0;
}
