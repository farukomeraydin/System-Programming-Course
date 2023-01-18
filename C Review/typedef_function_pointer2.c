#include <stdio.h>

typedef int(*PA)[5];

PA foo(void){
	static int a[5] = {1, 2, 3, 4, 5};
	return &a;
}

int main() {
	PA pa;
	int i;

	pa = foo();
	for (i = 0; i < 5; ++i)
		printf("%d ", (*pa)[i]);
	printf("\n");
	return 0;
}
