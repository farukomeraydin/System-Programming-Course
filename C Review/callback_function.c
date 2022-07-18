#include <stdio.h>

void foreach(const int* pi, size_t size, void (*pf)(int)) {
	size_t i;
	for (i = 0; i < size; ++i)
		pf(pi[i]);
}

void foo(int a) {
	printf("%d\n", a * a);
}

int main(void) {
	int a[] = { 10, 20, 30, 40, 50 };

	foreach(a, 5, foo);

	return 0;
}
