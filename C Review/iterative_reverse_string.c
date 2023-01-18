#include <stdio.h>

void putsrev(const char* str) {
	int i; //if i is size_t, when it decrements while equal to zero it won't be negative it will enter infinite loop.

	for (i = 0; str[i] != '\0'; ++i) //Moving to end of the string
		;

	for (--i; i >= 0; --i) //going back to the beginning of the string
		putchar(str[i]);
	putchar('\n');
}

int main(void) {
	putsrev("ankara");

	return 0;
}
