#include <stdio.h>
#include<malloc.h>
#include <string.h>




// 将字符串b追加到a的后面
void append(char *a, char *b)
{
	while (*a != '\0') {  
        a++;  
    }
	while ((*a++ = *b++) != '\0') {  
        ;  
    }
	*a = '\0';
}
// 将字符串b从索引[start, end]部分追加到a的后面
void append2(char *a, char *b, int start, int end)
{
	while (*a != '\0') {  
        a++;  
    }
	b = b + start;
	int i = 0;
	while ((i++ < (end - start + 1)) && (*a++ = *b++) != '\0') {  
        printf("%d\n", i);  
        printf("a=%s, b=%s\n", a-1, b);  
    }
	*a = '\0';
}
// 将字符串b从索引start的len个字符部分追加到a的后面
void append3(char *a, char *b, int start, int len)
{
	while (*a != '\0') {  
        a++;  
    }
	b = b + start;
	int i = 0;
	while ((i++ < len) && (*a++ = *b++) != '\0') {  
        ;  
    }
	*a = '\0';
}
// 打印指定len的字符串
void _printf(char *ch, int len)
{
	char *a = malloc(len+1);
	bzero(a, sizeof(a));
	char *b = a;
	int j = 0;
	for(;j < len; j++){
		*b++ = *ch++; 
	}
	printf("%s\n", a);
	free(a);
}

void test_printf()
{
	char ch[] = "abcdefg";
	printf("%s\n", ch);
	_printf(ch, 1);
	printf("%s\n", ch);
}




void test_append()
{
	char a[4] = "abc";  
    char b[4] = "def";
    char c[4] = "ghi";
	printf("a=%s, b=%s, c=%s\n", a, b, c);
    append(a, b);
	printf("a=%s, b=%s, c=%s\n", a, b, c);
    append(a, c);
	printf("a=%s, b=%s, c=%s\n", a, b, c);
}
void test_append2()
{
	char a[4] = "abc";  
    char b[4] = "def";
    char c[4] = "ghi";
	printf("a=%s, b=%s, c=%s\n", a, b, c);
    append2(a, b, 0,3);
	printf("a=%s, b=%s, c=%s\n", a, b, c);
}
void test_append3()
{
	char a[4] = "abc";  
    char b[4] = "def";
    char c[4] = "ghi";
	printf("a=%s, b=%s, c=%s\n", a, b, c);
    append3(a, b, 0,3);
	printf("a=%s, b=%s, c=%s\n", a, b, c);
}
// strncpy复制n个字符到dest中
void test_strncpy()
{
	char *src = "abc";
	char dest[100];
	bzero(dest, sizeof(dest));
	strncpy(dest, src, 4);
	printf("dest=%s\n", dest);
	char *src2="def";
	strncpy(dest, src2, 4);
	printf("dest=%s\n", dest);
}
int main(int argc, char **argv)
{
	test_strncpy();
}
