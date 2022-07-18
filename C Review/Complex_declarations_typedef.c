#include <stdio.h>

typedef int (*PF)(double);

int bar(double a) {
	printf("bar: %f\n", a);

	return 0;
}

PF foo(void) {
	return bar;
}

int main(void) {

	PF pf;

	pf = foo();
	pf(1.2);
	return 0;
}
