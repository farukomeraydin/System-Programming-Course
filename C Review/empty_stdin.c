#include <stdio.h>

void empty_stdin(void) {
	int ch;

	while ((ch = getchar()) != '\n' && ch != EOF)
		;
}

int main(void)
{
	int ch;
	char name[512];

	printf("Bir karakter giriniz:");
	fflush(stdout);

	ch = getchar();
	empty_stdin();

	printf("Bir isim giriniz:");
	fflush(stdout);

	gets(name); //works properly since stdin is emptied

	printf("'%c'  - \"%s\"\n", ch, name);

	return 0;
}
