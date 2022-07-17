#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

void exit_sys(const char *msg);


int main (void){
	if (chmod("test.txt", S_IRUSR | S_IWUSR) == -1)
		exit_sys("chmod");

	printf("success..!\n");
    return 0;
}
void exit_sys(const char *msg)
{
	perror(msg);

	exit(EXIT_FAILURE);
}
