#include <stdio.h>

int add(int a, int b) {
	return a + b;
}

int mul(int a, int b) {
	return a * b;
}

int sub(int a, int b) {
	return a - b;
}

int main(void) {
	int (*pf)(int, int);
	int result;

	pf = add;
	result = pf(10, 20);
	printf("%d\n", result);

	pf = mul;
	result = pf(10, 20);
	printf("%d\n", result);

	pf = sub;
	result = pf(10, 20);
	printf("%d\n", result);

	return 0;
}
