#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void exit_sys(const char *msg);


int main (void){
	if (unlink("test2.txt") == -1)
		exit_sys("unlink");

	printf("success\n");

    return 0;
}
void exit_sys(const char *msg)
{
	perror(msg);

	exit(EXIT_FAILURE);
}
