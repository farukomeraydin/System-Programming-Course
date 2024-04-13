#include <stdio.h>

int main(void) {
	__asm
	{
		cli //This assembly instruction is protected so the whole system would not fail.
	}


	return 0;
}
