#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

void ExitSys(LPCSTR lpszMsg);

int main(int argc, char* argv[]) {

	HANDLE hConsole;
	char text[] = "This is a test";
	COORD coord;
	DWORD dwWritten;
	WORD attrs[] = { FOREGROUND_BLUE, FOREGROUND_RED, FOREGROUND_GREEN };

	if ((hConsole = GetStdHandle(STD_OUTPUT_HANDLE)) == INVALID_HANDLE_VALUE)
		ExitSys("GetStdHandle");


	SetConsoleTextAttribute(hConsole, FOREGROUND_RED);

	coord.X = 10;
	coord.Y = 10;

	SetConsoleCursorPosition(hConsole, coord);
	WriteConsole(hConsole, text, strlen(text), &dwWritten, NULL);

	coord.X = 10;
	coord.Y = 11;

	SetConsoleCursorPosition(hConsole, coord);

	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
	WriteConsole(hConsole, text, strlen(text), &dwWritten, NULL);

	coord.X = 10;
	coord.Y = 12;
	SetConsoleCursorPosition(hConsole, coord);
	WriteConsole(hConsole, "ali", 3, &dwWritten, NULL);
	WriteConsoleOutputAttribute(hConsole, attrs, 3, coord, &dwWritten);

	getchar();
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
