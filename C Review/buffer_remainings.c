#include <stdio.h>

int main(void)
{
	int a, b;
	int result;
	char buf[100];

	result = scanf("%d%d", &a, &b);
	gets(buf);
	printf("%d\n", result);
	printf("Tamponda kalanlar:%s\n", buf); //what remained in buffer

	return 0;
}
