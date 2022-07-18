#include <stdio.h>

void foo(int a, int b) {

}

void bar(int a) {

}

void tar(void) {

}

int main(void) {
	void (*pf)();

	pf = foo;
	pf = bar;
	pf = tar;

	return 0;
}
