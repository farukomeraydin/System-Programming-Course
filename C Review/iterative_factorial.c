#include <stdio.h>

unsigned long long factorial(int n) { //If you want to keep 64 bits variable in 32 bits compilers you need to use long long type.
	unsigned long f = 1;
	int i;

	for (i = 2; i <= n; ++i)
		f *= i;

	return f;
}

int main(void) {
	unsigned long long result;
	result = factorial(10);
	printf("%llu\n", result);

	return 0;
}
