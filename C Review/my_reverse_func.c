#include <stdio.h>

void revstr(char* str) {
	size_t n, i;
	char temp;

	for (n = 0; str[n] != '\0'; ++n)
		;

	for (i = 0; i < n / 2; ++i) {
		temp = str[n - 1 - i];
		str[n - 1 - i] = str[i];
		str[i] = temp;
	}
}

int main(void) {
	char s[] = "ankara"; //not a constant literal
	revstr(s);
	puts(s);

	return 0;
}
