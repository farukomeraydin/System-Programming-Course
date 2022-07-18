#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int(*pa)[2];
	int i, k;

	pa = (int(*)[2])malloc(5 * sizeof(*pa));
	if (pa == NULL) {
		fprintf(stderr, "cannot allocate memory!..\n");
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < 5; ++i)
		for (k = 0; k < 2; ++k)
			pa[i][k] = i + k;

	for (i = 0; i < 5; ++i) {
		for (k = 0; k < 2; ++k)
			printf("%d ", pa[i][k]);
		printf("\n");
	}

	free(pa);
	return 0;
}
