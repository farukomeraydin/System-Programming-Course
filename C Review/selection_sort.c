#include <stdio.h>

#define SIZE	10

void ssort(int* pi, size_t size) {
	size_t i, k;
	size_t min_index;
	int min;

	for (i = 0; i < size - 1; ++i) {
		min_index = i;
		min = pi[i];
		for (k = i; k < size; ++k)
			if (pi[k] < min) {
				min = pi[k];
				min_index = k;
			}
		pi[min_index] = pi[i];
		pi[i] = min;
	}
}

void disp(const int* pi, size_t size) {
	size_t i;

	for (i = 0; i < size; ++i)
		printf("%d ", pi[i]);
	printf("\n");
}

int main(void) {
	int a[SIZE] = { 34, 12, 7, 84, 72, 39, 75, 45, 59, 21 };

	ssort(a, SIZE);

	disp(a, SIZE);

	return 0;
}
