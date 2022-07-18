#include <stdio.h>

void foo(void* pv, size_t size, size_t rowsize, size_t colsize, void (*proc)(void*)) {
	size_t i, k;
	char* pc = (char*)pv;

	for (i = 0; i < rowsize; ++i)
		for (k = 0; k < colsize; ++k)
			proc(pc + (i * colsize + k) * size);
}

void disp(void* pv) {
	printf("%d \n", *(int*)pv);
}

int main(void) {
	int a[3][3] = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
	foo(a, sizeof(int), 3, 3, disp);
	return 0;
}
