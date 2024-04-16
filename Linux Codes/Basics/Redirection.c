//stdout and stderr redirection. "./sample > x.txt" redirects stdout and stderr prints on screen. "./sample 2> x.txt"  redirects stderr and stdout prints on screen. "./sample > x.txt 2>y.txt" redirects both.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void exit_sys(const char *msg);

int main(void)
{
	int i;

	for (i = 0; i < 10; ++i){
		printf("stdout: %d\n", i);
		fprintf(stderr, "stderr: %d\n", i);
	}
	return 0;
}

void exit_sys(const char *msg)
{
	perror(msg);

	exit(EXIT_FAILURE);

}
