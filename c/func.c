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
int main(int argc, char **argv)
{
	int a = op(add, 1, 2);
	printf("%d\n", a);
	return 0;
}
