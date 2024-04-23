#include <stdio.h>

char* mygets(char* str) {
	int ch;
	size_t i;

	for (i = 0; (ch = getchar()) != '\n' && ch != EOF; ++i)
		str[i] = ch;

	if (i == 0 && ch == EOF)
		return NULL;

	str[i] = '\0';

	return str;
}

int main(void)
{
	char s[100];
	mygets(s);
	puts(s);

	return 0;
}
