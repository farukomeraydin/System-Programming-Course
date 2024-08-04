#include <stdio.h>

int main(void)
{
	int ch;
	char name[512];

	printf("Bir karakter giriniz:");
	fflush(stdout);

	ch = getchar(); //sonundaki \n karakteri tamponda kalır

	printf("Bir isim giriniz:");
	fflush(stdout);

	gets(name);

	printf("'%c'  - \"%s\"\n", ch, name);

	return 0;
}
