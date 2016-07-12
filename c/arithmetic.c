#include<stdio.h>
#include<stdlib.h>

void print_array(int a[], int len)
{
	int i = 0;
	for(; i < len; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
}
void sort_array(int a[], int len)
{
	int i = 0, j = 0;
	for(; i < len - 1; i++)
	{
		for(j = i + 1; j < len; j++)
		{
			if(a[i] > a[j])
			{
				int tmp = a[i];
				a[i] = a[j];
				a[j] = tmp;
			}
		}
	}

}
void print_char_array(char *a[], int len)
{
	int i = 0;
	for(; i < len; i++)
	{
		printf("%s ", a[i]);
	}
	printf("\n");
}
void sort_char_array(char *a[], int len)
{
	int i = 0, j = 0;
	for(; i < len - 1; i++)
	{
		for(j = i + 1; j < len; j++)
		{
			if(strcmp(a[i], a[j]) > 0)
			{
				char *tmp = a[i];
				a[i] = a[j];
				a[j] = tmp;
			}
		}
	}

}
int main(int argc, char **argv)
{
	int a[5] = {3, 2, 5, 1, 2};
	int len = sizeof(a) / sizeof(int);
	print_array(a, len);
	sort_array(a, len);
	print_array(a, len);
	char *str[5]={"aaaaab","bdsafc","asdcd","ed","sdfasdf"};
	print_char_array(str, 5);
	sort_char_array(str, 5);
	print_char_array(str, 5);
	return 0;
}
