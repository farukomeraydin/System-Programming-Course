#include <stdio.h>

int main(void)
{
	char* str = (char*)0xFC9999191919; //Random address is assigned.

	putchar(*str); //Trying to access the random address.
	printf("The end.\n");

	return 0;
}
