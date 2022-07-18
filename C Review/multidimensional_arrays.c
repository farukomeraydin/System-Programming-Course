#include <stdio.h>

int main(void) {
	int a[2] = { 10, 20 };
	int(*pia)[2];
	int val;

	pia = &a;

	//*pia is equivalent to a.
	val = (*pia)[0];
	printf("%d\n", val);

	val = (*pia)[1];
	printf("%d\n", val);

	return 0;
}
