#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

void ExitSys(LPCSTR lpszMsg);

int main(int argc, char* argv[]) {
	if (!RemoveDirectory("TestDir"))
		ExitSys("RemoveDirectory");

	printf("Ok\n");
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
