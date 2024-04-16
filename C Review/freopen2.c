#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int ch;

	while ((ch = fgetc(stdin)) != EOF)
		putchar(ch);


	return 0;

}
