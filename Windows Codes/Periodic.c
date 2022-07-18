#include <stdio.h>
#include <Windows.h>

void do_periodically(int period, void(*pf)(void)) {
	for (;;) {
		pf();
		Sleep(period);
	}
}

void foo(void) {
	putchar('.');
}

int main(void) {
	do_periodically(100, foo);

	return 0;
}
