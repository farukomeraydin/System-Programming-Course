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
	umask(S_IWUSR | S_IWOTH); /*default umask*/

	if ((fd = open("test2.txt", O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)) == -1)
		exit_sys("open");

	close(fd);
	printf("OK\n");

    return 0;
}
void exit_sys(const char *msg)
{
	perror(msg);

	exit(EXIT_FAILURE);
}
