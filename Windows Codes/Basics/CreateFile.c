#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

void ExitSys(LPCSTR lpszMsg);

int main(void) {
	HANDLE hFile;
	if ((hFile = CreateFile("Mest.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL)) == INVALID_HANDLE_VALUE)
		ExitSys("CreateFile");

	printf("Ok\n");

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
