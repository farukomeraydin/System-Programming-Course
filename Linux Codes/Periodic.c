#include <stdio.h>
#include <unistd.h>

void do_periodically(int period, void(*pf)(void))
{
	for (;;)  {
        pf();
		sleep(period);	
	}
}

void foo(void)
{
	putchar('.');
}

int main(void)
{
	do_periodically(0.8, foo);

	return 0;
}
