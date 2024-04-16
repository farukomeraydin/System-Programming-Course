#include <stdio.h>

int main(void)
{
	setvbuf(stdout, NULL, _IONBF, 0);
	printf("ali");

	for (;;)
		;

	return 0;
}
