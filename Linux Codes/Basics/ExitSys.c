#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

void exit_sys(const char *msg);

int main (void){

    int result;
    if ((result = open("test.dat", 0, O_RDONLY)) == -1)
    exit_sys("open");

    printf("success...\n");

    return 0;
}
void exit_sys(const char *msg)
{
	perror(msg);

	exit(EXIT_FAILURE);
}
