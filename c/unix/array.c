#include<stdio.h>
#include<string.h>
void print_array(int a[], int len)
{
	int i;
	printf("[");
	for(i = 0; i < len; i++)
	{
		printf("%d ", a[i]);
	}
	printf("]\n");
}
void test_array()
{
	// 定义数组, 首先必须初始化, 否则值不固定
	int a[10];
	printf("a[0]=%d\n", a[0]);//291017160
	bzero(a, sizeof(a));
	printf("a[0]=%d\n", a[0]);//0
	// 数组初始化
	int c[10]={1, 2, 3, 4, 5};
	print_array(c, 10);
	int i;
	// 遍历数组1
	for(i = 0; i < 10; i++)
	{
		a[i] = i;
		//printf("a[%d]=%d\n", i, a[i]);
	}
	print_array(a, 10);
	// 通过指针遍历数组2
	int *j, k;
	for(j = a, k = 0; j < a + 10; j++, k++)
	{
		*j = k;
		//printf("k=%d, j[%p]=%d\n", k, j, *j);
	}
	// 定义变长数组
	int n =2;
	int b[n];
	printf("b[0]=%d\n", b[0]);//291017160
	bzero(b, sizeof(b));
	printf("b[0]=%d\n", b[0]);//0
}

int main(int argc, char *argv[])
{
	test_array();
}
