#include <stdio.h>
#include <stdlib.h>


void foo(void) {
	int* a, * b, * c, * d;
	/*If any of it is unsuccessful, memory needs to be emptied.*/
	a = malloc(10);
	/*if (a == NULL)
		return;
	b = malloc(20);
	if (b == NULL) {
		free(a);
		return;
	}
	c = malloc(10);
	if (c == NULL) {
		free(a);
		free(b);
		return;
	}
	d = malloc(10);
	if (d == NULL) {
		free(a);
		free(b);
		free(c);
	}*/
	/*Yerine*/
	if (a == NULL)
		return;
	b = malloc(20);
	if (b == NULL)
		goto EXIT1;

	c = malloc(10);
	if (c == NULL)
		goto EXIT2;

	d = malloc(10);
	if (d == NULL)
		goto EXIT3;

EXIT3:
	free(c);
EXIT2:
	free(b);
EXIT1:
	free(a);

	/*In order to empty memory reversely, goto can be used.*/

}

int main(void) {

	return 0;
}
