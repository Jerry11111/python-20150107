#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
char * skip_str(char *buf)
{
	int i = 0;
	while(*(buf + i) != '\0'){
	    i++;
	}
	return buf + i + 1;
}
void test()
{
	char *str = "abcd\0efg1234";
	char *str2 = skip_str(str);
	printf("str: %s\n", str);
	printf("str2: %s\n", str2);
  
}

void test2()
{
	long curr_secs = time(NULL);
	printf("curr_secs: %ld\n", curr_secs);
	//uint8_t t :2 = 1;
	//printf("t: %d", t);
	char *str = "abcd\0efg1234";
	char *str2 = str;
	char *str3 = "";
	printf("str: %s\n", str);
	int i = 0;
	while(*(str + i) != '\0'){
	    i++;
	}
	str3 = str + i + 1;
	printf("str2: %s\n", str2);
	printf("str3: %s\n", str3);

}
int main(int argc,char* argv[])
{
	test();
	return 0;

}
