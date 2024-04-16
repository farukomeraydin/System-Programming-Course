#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	FILE* f;
	int ch;

	if (argc == 1)
		f = stdin;
	else
		if ((f = fopen(argv[1], "r")) == NULL){
			fprintf(stderr, "cannot open file: %s\n", argv[1]);
			exit(EXIT_FAILURE);
		}
	while((ch = fgetc(f)) != EOF)
		putchar(ch);

	fclose(f);

	return 0;
}
