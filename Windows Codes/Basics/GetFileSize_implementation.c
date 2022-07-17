#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

void ExitSys(LPCSTR lpszMsg);

int main(int argc, char* argv[]) {

	HANDLE hFile;
	DWORD dwSize;

	if ((hFile = CreateFile("Sample.c", GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL)) == INVALID_HANDLE_VALUE)
		ExitSys("CreateFile");

	if ((dwSize = GetFileSize(hFile, NULL)) == INVALID_FILE_SIZE)
		if (GetLastError() != NO_ERROR) //Length could be 0xFFFFFFFF so we need to check.
			ExitSys("GetFileSize");

	printf("%lu\n", (unsigned long)dwSize);
	CloseHandle(hFile);
	return 0;
}
void ExitSys(LPCSTR lpszMsg)
{
	DWORD dwLastError = GetLastError();
	LPTSTR lpszErr;

	if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, dwLastError,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpszErr, 0, NULL)) {
		fprintf(stderr, "%s (%lu): %s", lpszMsg, dwLastError, lpszErr);
		LocalFree(lpszErr);
	}

	exit(EXIT_FAILURE);
}
