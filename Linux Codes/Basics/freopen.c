#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	FILE* f;
	int i;

	if ((f = freopen("test.txt", "w", stdout)) == NULL) {
		fprintf(stderr, "Cannot open file!..\n");
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < 10; ++i)
		printf("%d\n", i);

	fclose(f);

	return 0;
}
