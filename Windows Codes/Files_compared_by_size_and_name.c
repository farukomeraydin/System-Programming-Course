#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

#define BLOCK_SIZE		10

void ExitSys(LPCSTR lpszMsg);
void Disp(const WIN32_FIND_DATA* files, size_t size);
int CompareBySize(const void* pv1, const void* pv2);
int CompareByName(const void* pv1, const void* pv2);

int main(void) {
	HANDLE hFileFind;
	WIN32_FIND_DATA finfo;
	WIN32_FIND_DATA* files;
	int count;

	if ((hFileFind = FindFirstFile("c:\\windows\\*.*", &finfo)) == INVALID_HANDLE_VALUE)
		ExitSys("FindFirstFile");

	count = 0;
	files = NULL;
	do {
		if (!(finfo.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
			if (count % BLOCK_SIZE == 0) {
				if ((files = (WIN32_FIND_DATA*)realloc(files, (count + BLOCK_SIZE) * sizeof(WIN32_FIND_DATA))) == NULL) {
					fprintf(stderr, "cannot allocate memory!..\n");
					exit(EXIT_FAILURE);
				}
			}
			files[count] = finfo;
			++count;
		}
	} while (FindNextFile(hFileFind, &finfo));

	qsort(files, count, sizeof(WIN32_FIND_DATA), CompareBySize);
	Disp(files, count);
	printf("----------------------------------\n");

	qsort(files, count, sizeof(WIN32_FIND_DATA), CompareByName);
	Disp(files, count);

	free(files);
	CloseHandle(hFileFind);

	return 0;
}

int CompareBySize(const void* pv1, const void* pv2) {
	const WIN32_FIND_DATA* f1 = (const WIN32_FIND_DATA*)pv1;
	const WIN32_FIND_DATA* f2 = (const WIN32_FIND_DATA*)pv2;

	if (f1->nFileSizeLow > f2->nFileSizeLow)
		return 1;
	if (f1->nFileSizeLow < f2->nFileSizeLow)
		return -1;
	return 0;
}

int CompareByName(const void* pv1, const void* pv2) {
	const WIN32_FIND_DATA* f1 = (const WIN32_FIND_DATA*)pv1;
	const WIN32_FIND_DATA* f2 = (const WIN32_FIND_DATA*)pv2;

	return _stricmp(f1->cFileName, f2->cFileName);
}

void Disp(const WIN32_FIND_DATA* files, size_t size) {
	size_t i;

	for (i = 0; i < size; ++i)
		printf("%-40s%lu\n", files[i].cFileName, (unsigned long int)files[i].nFileSizeLow);
}

void ExitSys(LPCSTR lpszMsg)
{
	DWORD dwLastError = GetLastError();
	LPTSTR lpszErr;

	if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, dwLastError,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpszErr, 0, NULL)) {
		fprintf(stderr, "%s: %s", lpszMsg, lpszErr);
		LocalFree(lpszErr);
	}

	exit(EXIT_FAILURE);
}
