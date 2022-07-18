#include <stdio.h>

void foo(void) {
	printf("foo\n");
}

typedef void (*PF)(void);

int main(void) {
	PF pf;	/*void(*pf)(void) pf;*/
	pf = foo;
	pf();

	return 0;
}
