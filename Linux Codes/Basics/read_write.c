#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void exit_sys(const char *msg);

int main(void)
{
	char buf[4096];
	ssize_t result;

	if ((result = read(0, buf, 1024)) == -1)
		exit_sys("read");

	if (write(1, buf, result) == -1)
		exit_sys("write");

	return 0;
}

void exit_sys(const char *msg)
{
	perror(msg);

	exit(EXIT_FAILURE);
}
