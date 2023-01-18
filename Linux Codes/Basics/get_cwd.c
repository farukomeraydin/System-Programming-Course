#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void exit_sys(const char* msg);

int main(void){
	char cwd[4096];

	if (getcwd(cwd, 4096) == NULL)
		exit_sys("getcwd");

	puts(cwd);
	return 0;
}

void exit_sys(const char* msg){
	perror(msg);
	exit(EXIT_FAILURE);
}
