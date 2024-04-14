#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void exit_sys(const char *msg);

int main(int argc, char *argv[])
{
	int fd;

	if ((fd = open("/dev/pts/0", O_WRONLY)) == -1)
		exit_sys("open");

	write(fd, "ankara", 6);

	close(fd);

	return 0;
}

void exit_sys(const char *msg)
{
	perror(msg);

	exit(EXIT_FAILURE);
}
