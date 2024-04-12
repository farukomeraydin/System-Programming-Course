#include <stdio.h>

void putint(long long n, int base) {
	if (n < 0) {
		n = -n;
		putchar('-');
	}

	if (n / base)
		putint(n / base, base);

	putchar(n % base > 9 ? n % base - 10 + 'A' : n % base + '0');
	//or
	//putchar((n % base > 9 ? -10 + 'A' : '0') + n % base);
}

int main(void) {
	putint(123, 16);
	return 0;
}
