#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

void ExitSys(LPCSTR lpszMsg);

int main(void) {
	HANDLE hFile;
	char buf[1024];
	DWORD dwRead;
	DWORD i;

	if ((hFile = CreateFile("Mest.txt", GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL)) == INVALID_HANDLE_VALUE)
		ExitSys("CreateFile");

	if (!ReadFile(hFile, buf, 5, &dwRead, NULL))
		ExitSys("ReadFile");

	buf[dwRead] = '\0';
	for (i = 0; i < dwRead; ++i)
		printf("%02X --> %c\n", (unsigned char)buf[i], buf[i]); //Cast to unsigned char so it is not casted to int


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
