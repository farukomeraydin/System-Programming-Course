#include <stdio.h>

void foo(int a) {
	printf("Giris: a = %d\n", a);

	if (a == 0)
		return;

	foo(a - 1); //when return happens it will continue from this line and printf below will be executed.When function calls itself everytime, new variable with the same name will be created.

	printf("Cikis: a = %d\n", a);
}


int main(void) {
	foo(5);
	return 0;
}
