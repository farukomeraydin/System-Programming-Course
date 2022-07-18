#include <stdio.h>

typedef int (*PF1)(long);

int tar(long a) {
	printf("tar: %ld\n", a);
	return 0;
}

PF1 bar(double a) {
	return tar;
}

typedef PF1(*PF2)(double);

PF2 foo(void) {
	printf("foo\n");
	return bar;
}

int main(void) {
	PF2 pf2;
	PF1 pf1;

	pf2 = foo();
	pf1 = pf2(1.2);
	pf1(0);

	return 0;
}
