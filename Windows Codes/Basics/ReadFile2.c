#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#define BUF_SIZE		4096

void ExitSys(LPCSTR lpszMsg);

int main(void) {
	HANDLE hFile;
	char buf[BUF_SIZE + 1];
	DWORD dwRead;

	if ((hFile = CreateFile("Mest.txt", GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL)) == INVALID_HANDLE_VALUE)
		ExitSys("CreateFile");

	for (;;) {
		if (!ReadFile(hFile, buf, BUF_SIZE, &dwRead, NULL))
			ExitSys("ReadFile");

		if (dwRead == 0)
			break;

		buf[dwRead] = '\0';
		printf("%s", buf);
	}
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
