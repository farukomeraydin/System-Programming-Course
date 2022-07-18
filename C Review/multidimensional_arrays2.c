#include <stdio.h>

int main(void) {
	int a[6] = { 1, 2, 3, 4, 5, 6 };
	int(*b)[2];
	int i, k;

	b = (int(*)[2])a;

	for (i = 0; i < 3; ++i) {
		for (k = 0; k < 2; ++k)
			printf("%d ", b[i][k]);
		printf("\n");
	}
	return 0;
}
