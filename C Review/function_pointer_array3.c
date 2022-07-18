#include <stdio.h>
#include <stdlib.h>

void foo(void) {
	printf("foo\n");
}

void bar(void) {
	printf("bar\n");
}

void tar(void) {
	printf("tar\n");
}

void car(void) {
	printf("car\n");
}

int main(void) {

	void (*pfs[4])(void);
	int i;
	pfs[0] = foo;
	pfs[1] = bar;
	pfs[2] = tar;
	pfs[3] = car;

	for (i = 0; i < 4; ++i)
		pfs[i]();

	return 0;
}
