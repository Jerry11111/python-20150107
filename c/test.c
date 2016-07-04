#include<stdio.h>
#include<limits.h>
#include<float.h>

int main(int argc, char **argv)
{
	
	printf("%s\n", __func__);// __func__表示函数名称
	printf("%d %d\n", INT_MIN, INT_MAX);
	printf("%f %f\n", FLT_MIN, FLT_MAX);
	return 0;
}
