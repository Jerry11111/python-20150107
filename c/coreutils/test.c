#include<stdio.h>
#include<unistd.h>
#include <stdbool.h>

void test()
{
	size_t t = 3;
	printf("[%zu] [%ld]\n", t, sizeof(t));
	printf("page size = %d Byte\n", getpagesize());
	bool x = true;
	printf("[%d]\n", x);
}
int main(int argc, char** argv)
{
	printf("[%d]\n", argc);	
	int i;
	for(i = 0; i < argc; i++){
		printf("%s ", argv[i]);
	}
	printf("\n");
}
