#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void exit_sys(const char *msg);


int main (void){

	printf("\x1B[10;10H");
	getchar();

    return 0;
}
void exit_sys(const char *msg)
{
	perror(msg);

	exit(EXIT_FAILURE);
}
