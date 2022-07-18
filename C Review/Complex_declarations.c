#include <stdio.h>

int bar(double a) {
	printf("bar: %f\n", a);

	return 0;
}

int (*foo(void))(double) {
	return bar;
}

int main(void) {

	int (*pf)(double);

	pf = foo();
	pf(1.2);
	return 0;
}
