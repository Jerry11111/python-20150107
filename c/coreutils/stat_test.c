#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
main()
{
	struct stat buf;
	int fd;
	fd = open("/etc/passwd", O_RDONLY);
	fstat(fd, &buf);
	printf("/etc/passwd file size +%zu\n ", buf.st_size);
}
