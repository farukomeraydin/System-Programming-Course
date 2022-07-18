#include <stdio.h>

int* foo(int* a) {
	return a;
}

int main(void) {
	int* (*pf)(int*);
	int a = 10;
	int* pi;

	pf = foo;
	pi = pf(&a);

	printf("%d\n", *pi);

	return 0;
}
