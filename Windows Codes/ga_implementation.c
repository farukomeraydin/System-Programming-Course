#include <stdio.h>
#include <stdlib.h>
#include "ga.h"


/*From Project Settings->Advanced section choose character set as "Not set"*/
int main(void) {
	InitGA();

	DrawFrame(10, 10, 20, 20);
	DrawFrame(22, 10, 25, 15);

	(void)getchar();
	return 0;
}
