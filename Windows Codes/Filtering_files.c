#include <stdio.h>
#include <string.h>
#include <Windows.h>


int ListDir(LPCSTR szPath, BOOL(*pf)(const WIN32_FIND_DATA*)) {
	HANDLE hFF;
	WIN32_FIND_DATA wfd;
	int result;

	if ((hFF = FindFirstFile(szPath, &wfd)) == INVALID_HANDLE_VALUE)
		return -1;

	do {
		if (!(wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && (result = pf(&wfd)) > 0)
			return result;
	} while (FindNextFile(hFF, &wfd));

	return 0;
}

int DispFile(const WIN32_FIND_DATA* pff) {
	printf("%s\n", pff->cFileName);

	return 0;
}

int FindFile(const WIN32_FIND_DATA* pff) {
	if (!_stricmp(pff->cFileName, "notepad.exe"))
		return 1;

	return 0;
}

BOOL Filter(const WIN32_FIND_DATA* pff) {
	long long size = (long long)pff->nFileSizeHigh << 32 | pff->nFileSizeLow;
	if (size < 1000)
		printf("%s, %lld\n", pff->cFileName, size);

	return TRUE;
}

int main(void) {
	int result;

	ListDir("c:\\windows\\*.*", DispFile);
	printf("-------------------------------\n");
	ListDir("c:\\windows\\*.*", Filter);
	printf("-------------------------------\n");

	if ((result = ListDir("c:\\windows\\*.*", FindFile)) == -1) {
		fprintf(stderr, "Path cannot find!..\n");
		exit(EXIT_FAILURE);
	}

	if (result > 0)
		printf("Found!..\n");
	else
		printf("Not found!..\n");



	return 0;
}
