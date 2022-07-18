#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void* pv1, const void* pv2) {
	const char** ppc1 = (const char**)pv1;
	const char** ppc2 = (const char**)pv2;

	return strcmp(*ppc1, *ppc2);
}

int main(void) {
	char* names[] = { "ali", "veli", "selami", "ayse", "fatma", "kazim" };
	int i;

	qsort(names, 6, sizeof(char*), compare);

	for (i = 0; i < 6; ++i)
		printf("%s ", names[i]);
	printf("\n");

	return 0;
}
