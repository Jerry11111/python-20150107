#include <stdio.h>
void test_type()
{
    int i =2;
	int size = sizeof(i);
	long l = 3;
	int lsize = sizeof(l);
	//printf("sizeof(i)=%l", sizeof(i));
   	printf("%d\n", size);
}
int main(int argc, char **argv)
{
	printf("Hello World!");
	test_type();
	return 0;
}

