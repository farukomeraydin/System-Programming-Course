#include <stdio.h>
#include <string.h>

int main(void)
{
	char s[10];
	char* str;

	if ((str = fgets(s, 10, stdin)) != NULL)
		if ((str = strchr(s, '\n')) != NULL)
			*str = '\0';

	if (str != NULL)
		puts(s);

	return 0;
}
