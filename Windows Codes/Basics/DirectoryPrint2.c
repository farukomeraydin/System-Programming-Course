#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <windows.h>

#define TABSIZE		4

void PutErrMsg(LPCSTR lpszmsg);

BOOL WalkDirRecur(LPCSTR lpszPath, BOOL(*Proc)(const WIN32_FIND_DATA*, int), int level) {
	HANDLE hFF;
	WIN32_FIND_DATA wfd;
	BOOL result;
	result = TRUE;

	if (!SetCurrentDirectory(lpszPath))
		return FALSE;


	if ((hFF = FindFirstFile("*.*", &wfd)) == INVALID_HANDLE_VALUE) //First file in the directory
		return FALSE;

	do {
		if (!Proc(&wfd, level)) { //If callback function fails returns FALSE
			result = FALSE;
			break;
		}
		if (!strcmp(wfd.cFileName, ".") || !strcmp(wfd.cFileName, "..")) //. and .. directories are not considered
			continue;

		if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			if (!WalkDirRecur(wfd.cFileName, Proc, level + 1)) { //If in previous call it exits the loop with FALSE, it should exit here too.
				result = FALSE;
				break;
			}

			if (!SetCurrentDirectory(".."))  //Should go back to upper directory
				break;

		}

	} while (FindNextFile(hFF, &wfd));

	FindClose(hFF);

	return result;
}

BOOL WalkDir(LPCSTR lpszPath, BOOL(*Proc)(const WIN32_FIND_DATA*, int)) {
	char cwd[MAX_PATH];
	BOOL result;

	if (_access(lpszPath, 0)) {
		fprintf(stderr, "Path not found: %s\n", lpszPath);
		return FALSE;
	}

	if (!GetCurrentDirectory(MAX_PATH, cwd)) {
		PutErrMsg("GetCurrentDirectory");
		return FALSE;
	}

	result = WalkDirRecur(lpszPath, Proc, 0);

	if (!SetCurrentDirectory(cwd)) {
		PutErrMsg("SetCurrentDirectory");
		return FALSE;
	}

	return result;
}

void PutErrMsg(LPCSTR lpszMsg) {
	DWORD dwLastErr = GetLastError();
	LPTSTR lpszErr;
	if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, dwLastErr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpszErr, 0, NULL)) {
		fprintf(stderr, "%s: %s", lpszMsg, lpszErr);
		LocalFree(lpszErr);
	}

}

BOOL Proc(const WIN32_FIND_DATA* wfd, int level) {
	printf("%*s%s %s\n", level * TABSIZE, "", wfd->cFileName, wfd->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ? "<DIR>" : "");

	if (!_strcmpi(wfd->cFileName, "Sample.c"))
		return FALSE;

	return TRUE;
}

int main(void)
{
	BOOL result;
	result = WalkDir("d:\\İleri C", Proc);
	printf("%s\n", result ? "Tree will be traversed entirely\n" : "Function terminated early\n");

	return 0;
}
