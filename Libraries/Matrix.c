#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"

HMATRIX CreateMatrix(size_t rowSize, size_t colSize) {
	HMATRIX hMatrix;

	if ((hMatrix = (HMATRIX)malloc(sizeof(MATRIX))) == NULL)
		return NULL;

	if ((hMatrix->pArray = (DATATYPE*)malloc(rowSize * colSize * sizeof(DATATYPE))) == NULL) {
		free(hMatrix);
		return NULL;
	}
	hMatrix->rowSize = rowSize;
	hMatrix->colSize = colSize;

	return hMatrix;
}
void CloseMatrix(HMATRIX hMatrix) {
	free(hMatrix->pArray);
	free(hMatrix);
}
BOOL SetElem(HMATRIX hMatrix, size_t row, size_t col, int val) {
	if (row >= hMatrix->rowSize || col >= hMatrix->colSize)
		return FALSE;

	hMatrix->pArray[row * hMatrix->colSize + col] = val;
	return TRUE;
}
int GetElem(HMATRIX hMatrix, size_t row, size_t col) {
	return hMatrix->pArray[row * hMatrix->colSize + col];
}

void DispMatrix(HMATRIX hMatrix) {
	size_t i, k;
	for (i = 0; i < hMatrix->rowSize; ++i) {
		for (k = 0; k < hMatrix->colSize; ++k)
			printf("%d ", GetElem(hMatrix, i, k)); //or hMatrix->pArray[i * hMatrix->colSize + k]
		printf("\n");
	}
}
