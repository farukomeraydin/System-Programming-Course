#include <stdio.h>

int(*foo(void))[5]{
	static int a[5] = {1, 2, 3, 4, 5};
	return &a;
}

int main() {
	int(*pa)[5];
	int i;

	pa = foo();
	for (i = 0; i < 5; ++i)
		printf("%d ", (*pa)[i]);
	printf("\n");
	return 0;
}
