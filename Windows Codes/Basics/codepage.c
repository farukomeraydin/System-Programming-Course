#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

int main(int argc, char* argv[]) {
	SetConsoleOutputCP(65001);
	printf("ağrı dağı\n");
	printf("%u\n", GetConsoleOutputCP());
	printf("%c\n", 'ş');

	return 0;
}
