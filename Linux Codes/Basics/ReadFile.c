#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

void exit_sys(const char *msg);


int main (void){

	int fd;
	unsigned char buf[1024];
	ssize_t result;
	ssize_t i;

	if ((fd = open("test.txt", O_RDONLY)) == -1)
		exit_sys("open");

	if ((result = read(fd, buf, 1024)) == -1)
		exit_sys("read");

	for (i = 0; i < result; ++i)
		printf("%02X%c", buf[i], i % 16 == 15 ? '\n' : ' ');
	printf("\n");

	printf("ok\n");


    return 0;
}
void exit_sys(const char *msg)
{
	perror(msg);

	exit(EXIT_FAILURE);
}
