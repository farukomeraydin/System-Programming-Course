#include <stdio.h>

unsigned long long factorial(int n) {
	if (n == 0)
		return 1;

	return n * factorial(n - 1);
}

int main(void) {
	unsigned long long result;

	result = factorial(4);
	printf("%llu\n", result);

	return 0;
}
