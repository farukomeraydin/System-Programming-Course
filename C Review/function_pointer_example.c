#include <stdio.h>

void foo(void) {
	printf("foo\n");
}


int main(void) {
	void (*pf)(void);
	pf = foo;

	pf();

	return 0;
}
