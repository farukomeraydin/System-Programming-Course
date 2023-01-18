#include <stdio.h>
#include <Windows.h>

void ExitSys(LPCSTR lpszMsg);

int main() {
	char *cwd;
	DWORD dwLen;

	if ((dwLen = GetCurrentDirectory(0, NULL)) == 0)
		ExitSys("GetCurrentDirectory");

	if ((cwd = (char*)malloc(dwLen)) == NULL) {
		fprintf(stderr, "cannot allocate memory!..\n");
		exit(EXIT_FAILURE);
	}

	if (!GetCurrentDirectory(dwLen, cwd))
		ExitSys("GetCurrentDirectory");

	printf("%s\n", cwd);
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
