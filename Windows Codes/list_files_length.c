#include <stdio.h>
#include <Windows.h>


BOOL ListDir(LPCSTR szPath, BOOL(*pf)(const WIN32_FIND_DATA*)) {
	HANDLE hFF;
	WIN32_FIND_DATA wfd;

	if ((hFF = FindFirstFile(szPath, &wfd)) == INVALID_HANDLE_VALUE)
		return FALSE;

	do {
		if (!(wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && !pf(&wfd))
			return FALSE;
	} while (FindNextFile(hFF, &wfd));

	return TRUE;
}

BOOL DispFile(const WIN32_FIND_DATA* pff) {
	printf("%s\n", pff->cFileName);

	return TRUE;
}

BOOL Filter(const WIN32_FIND_DATA* pff) {
	long long size = (long long)pff->nFileSizeHigh << 32 | pff->nFileSizeLow;
	if (size < 1000)
		printf("%s, %lld\n", pff->cFileName, size);

	return TRUE;
}

int main(void) {

	ListDir("c:\\windows\\*.*", DispFile);
	printf("-------------------------------\n");
	ListDir("c:\\windows\\*.*", Filter);

	return 0;
}
