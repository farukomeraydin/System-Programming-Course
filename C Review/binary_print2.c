#include <stdio.h>

void binprint(unsigned int n) {
	int i;
	
	for (i = 0; i < sizeof(n) * 8; ++i)
		if (n >> i == 0)
			break;

	for (--i; i >= 0; --i)
		putchar((n >> i & 1) + '0');
	putchar('\n');
}

int main(void) {
	binprint(21);
	return 0;
}
