#include <stdio.h>

int main(void) {
	int (*pf)(void) = main;
	//stack overflow
	printf("main\n");

	pf();

	return 0;
}
