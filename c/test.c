#include<stdio.h>
#include<limits.h>
#include<float.h>
#include <stdarg.h>
#include <string.h>
#include <sys/time.h>

void test1()
{
	printf("%s\n", __func__);// __func__表示函数名称
	printf("%d %d\n", INT_MIN, INT_MAX);
	printf("%f %f\n", FLT_MIN, FLT_MAX);

}
void test2()
{
}
void simple_va_fun(int i, ...) 
{ 
	va_list arg_ptr; 
	int j=0; 
	va_start(arg_ptr, i); 
	j=va_arg(arg_ptr, int); 
	va_end(arg_ptr); 
	printf("%d %d\n", i, j); 
}
void simple_va_fun2(char *format, ...) 
{ 
	va_list arg_ptr; 
	int j=0; 
	char str_tmp[50];
	va_start(arg_ptr, format); 
	j = vsnprintf(str_tmp, 50, format, arg_ptr);	
	va_end(arg_ptr); 
	printf("%d %s\n", j, str_tmp); 
}
void test_struct()
{
	struct User{
		int id;
		char username[10];
		short status;
		long birth;
	};
	struct User user1;
	printf("[%d | %s | %d | %ld]\n", user1.id, user1.username, user1.status, user1.birth);// 没有初始化, 都是确定的值
	bzero(&user1, sizeof(user1));// 执行初始化
	printf("[%d | %s | %d | %ld]\n", user1.id, user1.username, user1.status, user1.birth);// 没有初始化, 都是确定的值
	struct User user2 = {1, "root", 0, 123456};// 执行初始化, 无法以这样的形式赋值
	printf("[%d | %s | %d | %ld]\n", user2.id, user2.username, user2.status, user2.birth);// 没有初始化, 都是确定的值
	printf("%ld\n", sizeof(struct User));
	//printf("%d\n", user2.id);
}
void test_time()
{
	struct timeval tv;
	struct timezone tz;
	int res = gettimeofday(&tv, &tz);// 获取当前时间, 秒数
	printf("%d %ld %ld\n", res, tv.tv_sec, tv.tv_usec);
	//gettimeofday
}
int main(int argc, char **argv)
{
	//simple_va_fun(100); 
	//simple_va_fun(100, 200); 
	//simple_va_fun2("[%d %s]", 100, "hello world"); 
	test_struct();
	//test_time();
	return 0;
}
