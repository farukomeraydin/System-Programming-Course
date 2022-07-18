#include <stdio.h>

void foo(int a) {
	printf("foo: %d\n", a);
}

int main(void) {
	void (*pf)(void);
	void (*pf_original)(int);

	pf = (void(*)(void))foo; //type conversion for function pointer
	/*....*/

	pf_original = (void (*) (int))pf; //Before calling the function you must convert the function to its initial type, otherwise it will be undefined behaviour.
	pf_original(100);
	return 0;
}
