#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

/*Unicode code macros*/
#define BOX_UL		0x250C //Top-left corner
#define BOX_UR		0x2510 //Top-right corner
#define BOX_LL		0x2514 //Bottom-left corner
#define BOX_LR		0x2518 //Bottom-right corner
#define BOX_H		0x2500 //Horizontal line
#define BOX_V		0x2502 //Vertical line

static HANDLE hStdout;

BOOL InitGA(void) {
	if ((hStdout = GetStdHandle(STD_OUTPUT_HANDLE)) == INVALID_HANDLE_VALUE)
		return FALSE;

	return TRUE;
}

void Pos(int row, int col) {
	COORD coord;

	coord.X = col;
	coord.Y = row;

	SetConsoleCursorPosition(hStdout, coord);
}

void WriteChar(int row, int col, int ch) {
	COORD coord;
	DWORD dwWritten;
	char och = ch;

	coord.X = col;
	coord.Y = row;

	WriteConsoleOutputCharacter(hStdout, &och, 1, coord, &dwWritten);
}
void WriteCharAttr(int row, int col, int ch, int attr) {
	COORD coord;
	DWORD dwWritten;
	char och = ch;
	WORD wAttr = attr;

	coord.X = col;
	coord.Y = row;

	WriteConsoleOutputAttribute(hStdout, &wAttr, 1, coord, &dwWritten);
	WriteConsoleOutputCharacter(hStdout, &och, 1, coord, &dwWritten);
}

void WriteStr(int row, int col, LPCSTR szStr) {
	COORD coord;
	DWORD dwWritten;

	coord.X = col;
	coord.Y = row;

	WriteConsoleOutputCharacter(hStdout, szStr, strlen(szStr), coord, &dwWritten);
}

void WriteStrAttribute(int row, int col, LPCSTR szStr, int attr) {
	COORD coord;
	DWORD dwWritten;
	WORD wAttr = attr;
	int i;

	coord.X = col;
	coord.Y = row;


	for (i = 0; szStr[i] != '\0'; ++i) {
		WriteConsoleOutputAttribute(hStdout, &wAttr, 1, coord, &dwWritten);
		++coord.X;
	}
	coord.X = col;
	WriteConsoleOutputCharacter(hStdout, szStr, i, coord, &dwWritten);
}
void FillChar(int row, int col, int ch, int n) {
	int i;
	
	for (i = 0; i < n; ++i) {
		WriteChar(row, col, ch);
		++col;
	}
}

void FillCharAttr(int row, int col, int ch, int n, int attr) {
	int i;

	for (i = 0; i < n; ++i) {
		WriteCharAttr(row, col, ch, attr);
		++col;
	}
}

void VFillChar(int row, int col, int ch, int n) {
	int i;

	for (i = 0; i < n; ++i) {
		WriteChar(row, col, ch);
		++row;
	}
}
void VFillCharAttr(int row, int col, int ch, int n, int attr) {
	int i;

	for (i = 0; i < n; ++i) {
		WriteCharAttr(row, col, ch, attr);
		++row;
	}
}

void DrawFrame(int row1, int col1, int row2, int col2) {
	COORD coord;
	DWORD dwWritten;
	wchar_t ch;
	int i;

	coord.X = col1;
	coord.Y = row1;
	ch = BOX_UL;

	WriteConsoleOutputCharacterW(hStdout, &ch, 1, coord, &dwWritten);

	coord.X = col2;
	coord.Y = row1;
	ch = BOX_UR;

	WriteConsoleOutputCharacterW(hStdout, &ch, 1, coord, &dwWritten);

	coord.X = col1;
	coord.Y = row2;
	ch = BOX_LL;

	WriteConsoleOutputCharacterW(hStdout, &ch, 1, coord, &dwWritten);

	coord.X = col2;
	coord.Y = row2;
	ch = BOX_LR;

	WriteConsoleOutputCharacterW(hStdout, &ch, 1, coord, &dwWritten);

	ch = BOX_H;
	for (i = 0; i < col2 - col1 - 1; ++i) {
		coord.X = col1 + 1 + i;
		coord.Y = row1;
		WriteConsoleOutputCharacterW(hStdout, &ch, 1, coord, &dwWritten);
		coord.Y = row2;
		WriteConsoleOutputCharacterW(hStdout, &ch, 1, coord, &dwWritten);
	}

	ch = BOX_V;
	for (i = 0; i < row2 - row1 - 1; ++i) {
		coord.X = col1;
		coord.Y = row1 + 1 + i;
		WriteConsoleOutputCharacterW(hStdout, &ch, 1, coord, &dwWritten);
		coord.X = col2;
		WriteConsoleOutputCharacterW(hStdout, &ch, 1, coord, &dwWritten);
	}
}
