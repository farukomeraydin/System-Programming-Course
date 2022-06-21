#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#define BUF_SIZE		4096

void ExitSys(LPCSTR lpszMsg);

int main(int argc, char* argv[]) {
	HANDLE hFileSource, hFileDest;
	char buf[BUF_SIZE];
	DWORD dwRead, dwWritten;
	BOOL bResult;

	if (argc != 3) {
		fprintf(stderr, "wrong number of arguments!..\n");
		exit(EXIT_FAILURE);
	}

	if ((hFileSource = CreateFile(argv[1], GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL)) == INVALID_HANDLE_VALUE)
		ExitSys("CreateFile");

	if ((hFileDest = CreateFile(argv[2], GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL)) == INVALID_HANDLE_VALUE)
		ExitSys("CreateFile");

	while ((bResult = ReadFile(hFileSource, buf, BUF_SIZE, &dwRead, NULL)) && dwRead > 0) {
		if (!WriteFile(hFileDest, buf, dwRead, &dwWritten, NULL)) //Okurken son kısımda 4096dan az şey okursun dolayısıyla BUF_SIZE yazma
			ExitSys("WriteFile");
		if (dwWritten != dwRead) { //Okunan byte kadar yazılamamışsa
			fprintf(stderr, "Cannot file write maybe disk is full!..\n");
			exit(EXIT_FAILURE);
		}
	}
	if (!bResult)
		ExitSys("WriteFile");

	CloseHandle(hFileSource);
	CloseHandle(hFileDest);

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
