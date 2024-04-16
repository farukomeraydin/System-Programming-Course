#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	FILE* f;
	int val;

	if ((f = freopen("test.txt", "r", stdin)) == NULL) {
		fprintf(stderr, "Cannot open file!..\n");
		exit(EXIT_FAILURE);
	}

	while (scanf("%d", &val) == 1)
		printf("%d\n", val);

	return 0;

}
