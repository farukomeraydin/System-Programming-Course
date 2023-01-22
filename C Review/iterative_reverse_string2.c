#include <stdio.h>

void putsrev(const char* str) {
	char* rstr = (char*)str;

	while (*rstr != '\0')
		++rstr;

	for (--rstr; rstr >= str; --rstr)
		putchar(*rstr);
	putchar('\n');
}

int main(void) {
	putsrev("ankara");

	return 0;
}
