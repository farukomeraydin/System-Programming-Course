#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void WalkDir(LPCSTR lpszPath) {
	HANDLE hFF;
	WIN32_FIND_DATA wfd;

	if (!SetCurrentDirectory(lpszPath))
		return;

	if ((hFF = FindFirstFile("*.*", &wfd)) == INVALID_HANDLE_VALUE) //First file in the directory is found
		return;

	do {
		if (!strcmp(wfd.cFileName, ".") || !strcmp(wfd.cFileName, "..")) //. and .. directories are not considered
			continue;

		if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			printf("%s\n", wfd.cFileName);
			WalkDir(wfd.cFileName);
			if (!SetCurrentDirectory("..")) //Should go back to upper directory
				goto EXIT;
		}

	} while (FindNextFile(hFF, &wfd));

EXIT:
	FindClose(hFF);
}

int main(void)
{
	WalkDir("d:\\İleri C");

	return 0;
}
