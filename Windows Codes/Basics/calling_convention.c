#include <stdio.h>
#include <stdlib.h>

int __stdcall add(int a, int b) {
	return a + b;
}

int main(void) {
	int result;
	result = add(10, 20);
	printf("%d\n", result);

	return 0;
}
