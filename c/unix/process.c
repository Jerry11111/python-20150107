#include "header.h"
static void my_exit1(void);
static void my_exit2(void);
// atexit注册退出处理handler,并且处理顺序正好和注册的相反
int test_atexit()
{
	if (atexit(my_exit2) != 0)
		perror("can’t register my_exit2");
	if (atexit(my_exit1) != 0)
		perror("can’t register my_exit1");
	if (atexit(my_exit1) != 0)
		perror("can’t register my_exit1");
	printf("main is done\n");
	return 0;

}
// 打印传递的命令行参数, 第一个为程序的名称, 第二个为第一个参数,以此类推
int test_argv(int argc, char *argv[])
{
	int  i;
	for (i = 0; i < argc; i++) /* echo all command-line args */
	{
		printf("argv[%d]: %s\n", i, argv[i]);
	}
	return 0;
}
int main(int argc, char **argv)
{
	test_argv(argc, argv);
	return 0;
}
static void my_exit1(void)
{
	printf("first exit handler\n");
}
static void my_exit2(void)
{
	printf("second exit handler\n");
}
