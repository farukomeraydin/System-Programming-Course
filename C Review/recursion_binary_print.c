#include <stdio.h>

void binprint(unsigned int n) {
	if (n == 0)
		return;

	binprint(n >> 1);

	putchar((n & 1) + '0');
}

int main(void) {
	binprint(21);
	return 0;
}
