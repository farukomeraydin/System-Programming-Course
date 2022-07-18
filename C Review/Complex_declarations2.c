#include <stdio.h>


int tar(long a) {
	printf("tar: %ld\n", a);
	return 0;
}

int(*bar(double a))(long) {
	return tar;
}


int (*(*foo(void))(double))(long) {
	printf("foo\n");
	return bar;
}

int main(void) {
	int(*(*pf1)(double))(long);
	int (*pf2)(long);

	pf1 = foo();
	pf2 = pf1(1.2);
	pf2(0);

	return 0;
}
