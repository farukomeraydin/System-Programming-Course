#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

void PutErrMsg(LPCSTR lpszMsg);

void WalkDir(LPCSTR lpszPath) {
	HANDLE hFF;
	WIN32_FIND_DATA wfd;

	if (!SetCurrentDirectory(lpszPath)) {
		PutErrMsg(lpszPath);
		return;
	}



	if ((hFF = FindFirstFile("*.*", &wfd)) == INVALID_HANDLE_VALUE) //First file in the directory
		return;

	do {
		if (!strcmp(wfd.cFileName, ".") || !strcmp(wfd.cFileName, "..")) //. and .. directories are not considered.
			continue;

		if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			printf("%s\n", wfd.cFileName);
			WalkDir(wfd.cFileName);
			if (!SetCurrentDirectory("..")) { //Should go back to upper directory.
				PutErrMsg("..");
				goto EXIT;
			}
		}

	} while (FindNextFile(hFF, &wfd));

EXIT:
	FindClose(hFF);
}
void PutErrMsg(LPCSTR lpszMsg) {
	DWORD dwLastErr = GetLastError();
	LPTSTR lpszErr;
	if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, dwLastErr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpszErr, 0, NULL)) {
		fprintf(stderr, "%s: %s", lpszMsg, lpszErr);
		LocalFree(lpszErr);
	}

}

int main(void)
{
	WalkDir("d:\\İleri C");

	return 0;
}
