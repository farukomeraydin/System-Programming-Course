#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void ExitSys(LPCSTR lpszMsg);

int main(void)
{
	HANDLE hStdin, hStdout;
	char buf[4096];
	DWORD dwRead, dwWritten;

	if ((hStdin = GetStdHandle(STD_INPUT_HANDLE)) == INVALID_HANDLE_VALUE)
		ExitSys("GetStdHandle");

	if ((hStdout = GetStdHandle(STD_OUTPUT_HANDLE)) == INVALID_HANDLE_VALUE)
		ExitSys("GetStdHandle");

	if (!ReadFile(hStdin, buf, 4096, &dwRead, NULL))
		ExitSys("ReadFile");

	if (!WriteFile(hStdout, buf, dwRead, &dwWritten, NULL))
		ExitSys("WriteFile");

	return 0;
}

void ExitSys(LPCSTR lpszMsg)
{
	DWORD dwLastErr = GetLastError();
	LPTSTR lpszErr;

	if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, dwLastErr,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpszErr, 0, NULL)) {
		fprintf(stderr, "%s: %s", lpszMsg, lpszErr);
		LocalFree(lpszErr);
	}

	exit(EXIT_FAILURE);

}
