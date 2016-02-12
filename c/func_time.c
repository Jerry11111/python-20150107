#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
int main(int argc,char* argv[])
{
	long curr_secs = time(NULL);
	printf("curr_secs: %ld", curr_secs);
	uint8_t t :2 = 1;
	printf("t: %d", t);
	return 0;
}
