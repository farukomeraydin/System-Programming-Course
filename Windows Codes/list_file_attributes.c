#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

void ExitSys(LPCSTR lpszMsg);

int main(int argc, char* argv[]) {
	HANDLE hFF;
	WIN32_FIND_DATA wfd;
	unsigned long long ullSize;
	SYSTEMTIME st;

	if ((hFF = FindFirstFile("C:\\windows\\*.*", &wfd)) == NULL)
		ExitSys("FindFirstFile");

	do {
		printf("%-30s", wfd.cFileName);

		if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			printf("<DIR>\n");
		else
		{
			ullSize = (unsigned long long)wfd.nFileSizeHigh << 32 | wfd.nFileSizeLow;
			printf("\nFile Size: %llu\n", ullSize);
		}
		FileTimeToSystemTime(&wfd.ftLastWriteTime, &st);
		printf("Last Update: %02d/%02d/%4d %02d:%02d:%02d\n", st.wDay, st.wMonth, st.wYear, st.wHour, st.wMinute, st.wSecond);
		FileTimeToSystemTime(&wfd.ftLastAccessTime, &st);
		printf("Last Read: %02d/%02d/%4d %02d:%02d:%02d\n", st.wDay, st.wMonth, st.wYear, st.wHour, st.wMinute, st.wSecond);
		FileTimeToSystemTime(&wfd.ftCreationTime, &st);
		printf("Creation: %02d/%02d/%4d %02d:%02d:%02d\n", st.wDay, st.wMonth, st.wYear, st.wHour, st.wMinute, st.wSecond);

		printf("\n");
		printf("----------------------------------------------------------\n");

	} while (FindNextFile(hFF, &wfd));

	FindClose(hFF);

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
