#include <stdio.h>

#define SIZE	10

void ssort(int* pi, size_t size) {
	int max;
	size_t max_index, i;

	if (size == 1)
		return;

	max = pi[0];
	max_index = 0;

	for (i = 1; i < size; ++i)
		if (pi[i] > max) {
			max = pi[i];
			max_index = i;
		}
	pi[max_index] = pi[size - 1];
	pi[size - 1] = max;

	ssort(pi, size - 1);
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
