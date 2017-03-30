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
	struct User user2 = {1, "root", 0, 123456};// 执行初始化
	printf("[%d | %s | %d | %ld]\n", user2.id, user2.username, user2.status, user2.birth);// 没有初始化, 都是确定的值
	struct User user3 ={
		.id = 2,
		.username = "root2",
		.status = 2,
		.birth = 2,
	};
	printf("[%d | %s | %d | %ld]\n", user3.id, user3.username, user3.status, user3.birth);// 没有初始化, 都是确定的值
	printf("%ld\n", sizeof(struct User));
	//printf("%d\n", user2.id);
}
void test_union()
{
	// 如果struct中union不存在变量名称, 引用为.a
	// 如果struct中union存在变量名称, 那么引用的时候要加上这个名称, .data.a, 而不能是.a
	struct User{
		int id;
		union{
			int a;
			int b;
		};
	} user = {
		.id = 1,
		.a = 2,
		.b = 3,
	};
	printf("%d %d %d\n", user.id, user.a, user.b);
	struct User2{
		int id;
		union Data{
			int a;
			int b;
		}data;
	} user2 = {
		.id = 1,
		.data.a = 2,
		.data.b = 3,
	};
	//printf("%d %d %d\n", user2.id, user2.a, user2.b);// 错误
	printf("%d %d %d\n", user2.id, user2.data.a, user2.data.b);

}
void test_time()
{
	struct timeval tv;
	struct timezone tz;
	int res = gettimeofday(&tv, &tz);// 获取当前时间, 秒数
	printf("%d %ld %ld\n", res, tv.tv_sec, tv.tv_usec);
	time_t tm = time(NULL);
	printf("%ld\n", tm);
	//gettimeofday
}
int main(int argc, char **argv)
{
	//simple_va_fun(100); 
	//simple_va_fun(100, 200); 
	//simple_va_fun2("[%d %s]", 100, "hello world"); 
	//test_struct();
//	test_union();
	test_time();
	return 0;
}
