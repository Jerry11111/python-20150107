#include "header.h"
#include <pwd.h>
#include <shadow.h>
#include <grp.h>
// 读取/etc/passwd文件
void op_passwd()
{
	struct passwd *ptr;
	char name[] = "root";
	// 将指针移到开始位置
	setpwent();
	// 获取第一条记录
	while((ptr = getpwent()) != NULL)
	{
		//if (strcmp(name, ptr->pw_name) == 0)
		//{
		//	printf("pw_name:%s, pw_uid:%d, pw_shell:%s\n", ptr->pw_name, ptr->pw_uid, ptr->pw_shell);
		//	break;   	
		//}
		printf("pw_name:%s, pw_uid:%d, pw_shell:%s\n", ptr->pw_name, ptr->pw_uid, ptr->pw_shell);
	}
	// 结束读取
	endpwent();
}
// 读取/etc/shadow文件
// 执行时sudo, 才能读取到
void op_shadow()
{
	struct spwd *sp;
	char name[] = "root";
	// 将指针移到开始位置
	setspent();
	// 获取第一条记录
	while((sp = getspent()) != NULL)
	{
		//if (strcmp(name, sp->pw_name) == 0)
		//{
		//	printf("pw_name:%s, pw_uid:%d, pw_shell:%s\n", ptr->pw_name, ptr->pw_uid, ptr->pw_shell);
		//	break;   	
		//}
		printf("sp_namp:%s, sp_pwdp:%s, sp_expire:%ld\n", sp->sp_namp, sp->sp_pwdp, sp->sp_expire);
	}
	// 结束读取
	endspent();
}
void op_group()
{
	struct group *sp;
	char name[] = "root";
	// 将指针移到开始位置
	setgrent();
	// 获取第一条记录
	while((sp = getgrent()) != NULL)
	{
		//if (strcmp(name, sp->pw_name) == 0)
		//{
		//	printf("pw_name:%s, pw_uid:%d, pw_shell:%s\n", ptr->pw_name, ptr->pw_uid, ptr->pw_shell);
		//	break;   	
		//}
		printf("gr_name:%s, gr_passwd:%s, gr_gid:%d\n", sp->gr_name, sp->gr_passwd, sp->gr_gid);
	}
	// 结束读取
	endgrent();
}
int main(int argc, char **argv)
{
	op_group();
	return 0;
}
