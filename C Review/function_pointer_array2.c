#include <stdio.h>

void foo(void) {
	printf("foo\n");
}

void bar(void) {
	printf("bar\n");
}

void tar(void) {
	printf("tar\n");
}

int main(void) {
	void (*a[3])(void) = { foo, bar, tar };
	int i;

	for (i = 0; i < 3; ++i)
		a[i]();

	return 0;
}
