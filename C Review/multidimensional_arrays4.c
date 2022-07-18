#include <stdio.h>

void foo(const int* pi, size_t rowsize, size_t colsize) {
	size_t i, k;
	for (i = 0; i < rowsize; ++i) {
		for (k = 0; k < colsize; ++k)
			printf("%d ", *(pi + i * colsize + k));
		printf("\n");
	}
}

int main(void) {
	int a[3][3] = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
	foo((int*)a, 3, 3);
	return 0;
}
