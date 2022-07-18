#include <stdio.h>

void foo(int a) {
	printf("foo: %d\n", a);
}

int main(void) {
	void* pv;
	void (*pf)(int);

	//pv = pf; /*In C and C++ it is invalid but most of the compilers forgive it*/

	pv = *(void**)&pf;   /*It is invalid but we used a trick to make it work*/
	*(void**)&pf = pv;
	return 0;
}
