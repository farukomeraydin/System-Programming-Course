#include <stdio.h>


void foo(void) {
	static int count = 0;
	printf("%d\n", count + 1);
	++count;

	foo();
}

int main() {
	foo();
	return 0;
}
