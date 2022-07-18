#include <stdio.h>
#include <time.h>
#include <Windows.h>

void do_periodically(int period, void(*pf)(void)) {
	for (;;) {
		pf();
		Sleep(period);
	}
}

void put_clock(void) {
	struct tm* pt;
	time_t t;

	time(&t);
	pt = localtime(&t);
	printf("%02d:%02d:%02d\r", pt->tm_hour, pt->tm_min, pt->tm_sec);
}

int main(void) {
	do_periodically(1000, put_clock);

	return 0;
}
