#include <stdio.h>

int main(void) {
	char* names[] = { "ali", "veli", "selami" };
	char** str;

	str = names;

	puts(*str);
	++str;
	puts(*str);
	++str;
	puts(*str);

	return 0;
}
