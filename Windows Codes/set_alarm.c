#include <stdio.h>
#include <time.h>
#include <Windows.h>

void do_alarm(int hour, int minute, int second, void (*pf)(void)) {
	time_t t;
	struct tm* ptime;
	for (;;) {
		t = time(NULL);
		ptime = localtime(&t);

		if (ptime->tm_hour == hour && ptime->tm_min == minute && ptime->tm_sec == second) {
			pf();
			break;
		}
		Sleep(100);
	}
}

void alarm_proc(void) {
	printf("ALARM..\n");
}

int main(void) {
	do_alarm(18, 19, 10, alarm_proc);

	return 0;
}
