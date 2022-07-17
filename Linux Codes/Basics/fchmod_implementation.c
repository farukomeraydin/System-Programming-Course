#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void exit_sys(const char *msg);


int main (void){
	int fd;
	if ((fd = open("test.txt", O_RDONLY)) == -1)
		exit_sys("open");

	if (fchmod(fd, S_IRUSR | S_IWUSR) == -1)
		exit_sys("fchmod");

	close(fd);
	printf("success..!\n");
    return 0;
}
void exit_sys(const char *msg)
{
	perror(msg);

	exit(EXIT_FAILURE);
}
