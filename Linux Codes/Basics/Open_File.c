#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

void exit_sys(const char *msg);


int main (void){

	int fd;
	if ((fd = open("test.txt", O_RDWR)) == -1)
		exit_sys("open");

	printf("ok\n");


    return 0;
}
void exit_sys(const char *msg)
{
	perror(msg);

	exit(EXIT_FAILURE);
}
