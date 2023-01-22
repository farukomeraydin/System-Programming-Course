#include <stdio.h>

void revstr_recur(char* str, size_t left, size_t right) {
	char temp;
	while (left >= right)
		return;
	
	temp = str[left];
	str[left] = str[right];
	str[right] = temp;

	revstr_recur(str, left + 1, right - 1);
}

void revstr(char* str) {
	size_t i;

	if (*str == '\0') //check if empty
		return;

	for (i = 0; str[i] != '\0'; ++i)
		;

	revstr_recur(str, 0, i - 1);
}

int main(void) {
	char s[] = "ankara";
	revstr(s);
	puts(s);

	return 0;
}
