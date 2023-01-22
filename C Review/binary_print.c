#include <stdio.h>

void binprint(unsigned int n) {
	int i;
	
	for (i = sizeof(n) * 8 - 1; i >= 0; --i)
		if (n >> i & 1) //We need to break as soon as we get '1' bit
			break;

	for (; i >= 0; --i)
		putchar((n >> i & 1) + '0');
	putchar('\n');
}

int main(void) {
	binprint(21);
	return 0;
}
