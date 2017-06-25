#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdio.h>
#include <sys/syscall.h>

void test(){
	int rc;
	rc = chmod("/etc/passwd", 0444);
	if (rc == -1)
		fprintf(stderr, "chmod failed, errno = %d\n", errno);
	else
		printf("chmod success!\n");
}
void test2(){
	int rc;
	rc = syscall(SYS_chmod, "/etc/passwd", 0444);
	if (rc == -1)
		fprintf(stderr, "chmod failed, errno = %d\n", errno);
	else
		printf("chmod succeess!\n");
}
void test3(){
	long rc;
	char *file_name = "/etc/passwd";
	unsigned short mode = 0444;
	asm(
			"int $0x80"
			: "=a" (rc)
			: "0" (SYS_chmod), "b" ((long)file_name), "c" ((long)mode)
	   );
	if ((unsigned long)rc >= (unsigned long)-132) {
		errno = -rc;
		rc = -1;
	}
	if (rc == -1)
		fprintf(stderr, "chmode failed, errno = %d\n", errno);
	else
		printf("success!\n");
}
int main(){
	test3();
	return 0;
}


