#include <stdio.h>
struct foo {
    int a, b;
};
void test_type()
{
    int i =2;
	int size = sizeof(i);
   	printf("sizeof(int)=%d\n", size);// 4
	long l = 3;
	int lsize = sizeof(l);
   	printf("sizeof(long)=%d\n", lsize);// 8
	char c = 'a';
	int csize = sizeof(c);
   	printf("sizeof(char)=%d\n", csize);// 1
}
/**
	typedef给已知的数据类型重命名
**/
void test_typedef()
{
	typedef int int_def;
	int_def i =1;
	int size = sizeof(i);
   	printf("sizeof(char)=%d\n", size);// 1
}
void test_pointer()
{
	char *x = NULL;
    printf("%p\n", x);
    printf("%p\n", (struct foo *)x + 4);
    printf("%p\n", (struct foo *)(x + 4));
}
int main(int argc, char **argv)
{
	printf("Hello World!\n");
//	test_type();
	//test_typedef();
    test_pointer();
	return 0;
}


