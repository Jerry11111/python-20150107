#include "header.h"
#include <math.h>

void func_pointer()
{
	double Add(double x, double y)
	{
		return x + y;
	}
	double Sub(double x, double y)
	{
		return x - y;
	}
	double Mul(double x, double y)
	{
		return x * y;
	}
	double Div(double x, double y)
	{
		return x / y;
	}
	// 5个函数指针数组, 这些函数需要两个double参数, 且返回值也是double
	double (*funcTable[5])(double, double) = {Add, Sub, Mul, Div, pow};
	// 字符串指针数组
	char *msgTable[5] = {"Sum", "Difference", "Product", "Quotient", "Power"};
	int i;
	double x = 0, y = 0;
	printf("Enter two operands for some arithmetic:\n");
	if(scanf("%lf %lf", &x, &y) != 2)
	{
		printf("Invalid input: \n");
	}
	for(i = 0; i < 5; ++i)
	{
		printf("%10s: %6.2f\n", msgTable[i], funcTable[i](x, y));
	}
}
void func_pointer2()
{
	double Add(double x, double y)
	{
		return x + y;
	}
	double Sub(double x, double y)
	{
		return x - y;
	}
	double Mul(double x, double y)
	{
		return x * y;
	}
	double Div(double x, double y)
	{
		return x / y;
	}
	// 将函数作为参数传递
	double cal( double (*func)(double, double), double x, double y)
	{
		return func(x, y);
	}
	double x = 1.0;
	double y = 2.0;
	double z = cal(Add, x, y);
	printf("%f %s %f = %f\n", x, "+", y, z);
}

int main(int argc, char **argv)
{
	func_pointer2();	
	return 0;
}
