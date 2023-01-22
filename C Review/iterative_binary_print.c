#include <stdio.h>

void binprint(unsigned int n) {
	int i;
	
	for (i = sizeof(n) * 8 - 1; i >= 0; --i) //We need to know the size in order to print from MSB.
		putchar((n >> i & 1) + '0');
	putchar('\n');
}

int main(void) {
	binprint(21);
	return 0;
}
