#include <stdio.h>

void putint(long long n) {
	if (n < 0) {
		n = -n;
		putchar('-');
	}

	if (n / 10)
		putint(n / 10);

	putchar(n % 10 + '0');
}

int main(void) {
	putint(1234);
	return 0;
}
