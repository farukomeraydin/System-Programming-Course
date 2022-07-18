#include <stdio.h>

int main(void) {
	const int a = 10;
	const int** ppi;
	int* pi;
	ppi = &pi; //If this was valid, assignment in 10th line would be valid. 
	*ppi = &a;
	*pi = 20;
	//pi = &a; //Assignment in the 7th line is invalid so this assignment can be invalid too.
	return 0;
}
