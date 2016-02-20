#include <stdio.h>
struct foo {
    int a, b;
};
struct stu1
{
  int i;
  char c;
  int j;
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
    int stsize = sizeof(struct stu1);
   	printf("sizeof(stu1)=%d\n", stsize);// 1
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
    printf("%p\n", (struct foo *)x + 4);//0x20
    printf("%p\n", (struct foo *)(x + 4));//0x04
	char *x2 = NULL;
	char chs[]="chs";
	x2 = chs;
	char chs2[]="chs2";
    printf("%s\n", x2);

}
void test_variable()
{
   char chs[6] = "abcd";
   printf("chs = %s\n", chs);
   char *chsp = (char *)&chs[0];
   //chsp = "12345";
   //chs[0] = '1';
   chsp = NULL;
   printf("chs = %s\n", chs);
   printf("chsp = %s\n", chsp);
}
int main(int argc, char **argv)
{
	printf("Hello World!\n");
       //	test_type();
       //test_variable();
	//test_typedef();
    test_pointer();
	return 0;
}


