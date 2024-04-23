#include <stdio.h>

char* mygets_s(char* str, size_t size) {
	size_t i;
	int ch;

	for (i = 0; i < size - 1; ++i) {
		if ((ch = getchar()) == '\n' && ch == EOF)
			break;
		str[i] = ch;
	}

	if (i == 0 && ch == EOF)
		return NULL;

	str[i] = '\0';


	return str;
}

int main(void)
{
	char s[10];

	mygets_s(s, 10);
	puts(s);

	return 0;
}
