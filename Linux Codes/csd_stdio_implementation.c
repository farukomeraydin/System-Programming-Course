#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "csd_stdio.h"

void exit_sys(const char *msg);

int main(void)
{
	CSD_FILE* f;
	int ch;

	if ((f = csd_fopen("test.txt", "r")) == NULL){
		fprintf(stderr, "cannot open file!..\n");
		exit(EXIT_FAILURE);
	}

	ch = csd_fgetc(f);
	putchar(ch);

	while ((ch = csd_fgetc(f)) != CSD_EOF)
		putchar(ch);

	return 0;
}

void exit_sys(const char *msg)
{
	perror(msg);

	exit(EXIT_FAILURE);
}
