#include <stdio.h>
#include <stdlib.h>

typedef char* STR[3];

int main(void) {
	STR names = { "ali", "veli", "selami" };
	//equivalent
	//char* names[3] = { "ali", "veli", "selami" };
	puts(names[0]);
	return 0;
}
