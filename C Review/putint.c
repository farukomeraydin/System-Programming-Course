#include <stdio.h>
#include <math.h>

void putint(long long n) {
	char s[32];
	int ndigit, nflag;

	nflag = 0;
	if (n < 0) {
		n = -n;
		nflag = 1;
	}

	ndigit = (int)log10(n) + 1 + nflag;
	s[ndigit--] = '\0';

	while (n) {
		s[ndigit--] = n % 10 + '0';
		n /= 10;
	}

	if (nflag)
		s[ndigit] = '-';

	for (ndigit = 0; s[ndigit] != '\0'; ++ndigit)
		putchar(s[ndigit]);

	putchar('\n');
}

int main(void) {
	putint(1234);
	return 0;
}
