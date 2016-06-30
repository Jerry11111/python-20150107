#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
void append(char *a, char *b, int start, int len)
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
