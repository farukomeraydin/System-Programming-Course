#include <stdio.h>

int main(void)
{
	char s[100];
	char* str;

	str = gets(s);
	
	if (str == NULL)
		printf("Null pointer!..\n");
	else
		puts(s);

	return 0;
}
