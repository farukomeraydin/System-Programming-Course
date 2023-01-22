#include <stdio.h>
#include <string.h>

void revstr(char* str, size_t left, size_t right) {
	char temp;
	while (left >= right)
		return;
	
	temp = str[left];
	str[left] = str[right];
	str[right] = temp;

	revstr(str, left + 1, right - 1);
}

int main(void) {
	char s[] = "ankara";
	revstr(s, 0, strlen(s) - 1);
	puts(s);

	return 0;
}
