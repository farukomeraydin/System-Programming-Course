#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"

int main(void) {

	HMATRIX hMatrix;

	if ((hMatrix = CreateMatrix(3, 3)) == NULL) {
		fprintf(stderr, "cannot create matrix!..\n");
		exit(EXIT_FAILURE);
	}

	SetElem(hMatrix, 0, 0, 1);
	SetElem(hMatrix, 0, 1, 2);
	SetElem(hMatrix, 0, 2, 3);

	SetElem(hMatrix, 1, 0, 4);
	SetElem(hMatrix, 1, 1, 5);
	SetElem(hMatrix, 1, 2, 6);

	SetElem(hMatrix, 2, 0, 7);
	SetElem(hMatrix, 2, 1, 8);
	SetElem(hMatrix, 2, 2, 9);

	DispMatrix(hMatrix);

	CloseMatrix(hMatrix);

	return 0;
}
