#include <stdio.h>
#include <string.h>
#include <Windows.h>

#define MAX_CMD_LINE	4096
#define MAX_CMD_PARAMS	64

struct CMD {
	char* cmd_text;
	void (*proc)(void);
};

void ExitSys(LPCSTR);
void ParseCmdLine(void);
void DirProc(void);
void CopyProc(void);
void ClsProc(void);
void RenameProc(void);
void ChangeDirProc(void);
void DispDirectory(LPCTSTR lpszPath);

char g_cmd_line[MAX_CMD_LINE];

struct CMD g_cmds[] = {
	{"dir", DirProc},
	{"copy", CopyProc},
	{"cls", ClsProc},
	{"rename", RenameProc},
	{"cd", ChangeDirProc},
	{NULL, NULL},
};

char* g_params[MAX_CMD_PARAMS];
int g_nparams;
char g_cwd[MAX_PATH];

int main(void) {
	char* str;
	int i;

	if (!GetCurrentDirectory(MAX_PATH, g_cwd))
		ExitSys("GetCurrentDirectory");


	for (;;) {
		printf("%s>", g_cwd);
		fgets(g_cmd_line, MAX_CMD_LINE, stdin); //gets new line too.
		if ((str = strchr(g_cmd_line, '\n')) != NULL)
			*str = '\0';

		ParseCmdLine();
		if (g_nparams == 0)
			continue;
		if (!strcmp(g_params[0], "exit"))
			break;
		for (i = 0; g_cmds[i].cmd_text != NULL; ++i)
			if (!strcmp(g_cmds[i].cmd_text, g_params[0])) {
				g_cmds[i].proc();
				break;
			}
		if (g_cmds[i].cmd_text == NULL)
			printf("command not found: %s\n\n", g_params[0]);
	}
	return 0;
}

void ParseCmdLine(void) {
	char* str;

	g_nparams = 0;
	for (str = strtok(g_cmd_line, " \t"); str != NULL; str = strtok(NULL, " \t"))
		g_params[g_nparams++] = str;
	g_params[g_nparams] = NULL;
}
void DirProc(void) {

	if (g_nparams > 2) {
		printf("too many arguments!..\n\n");
		return;
	}

	DispDirectory(g_nparams == 1 ? g_cwd : g_params[1]);
}

void CopyProc(void) {
	if (g_nparams != 3) {
		printf("wrong number of arguments!..\n\n");
		return;
	}
}

void ClsProc(void) {
	if (g_nparams != 1) {
		printf("too many arguments!..\n\n");
		return;
	}

	printf("cls command\n");
}

void RenameProc(void) {
	printf("rename command\n");
}

void ChangeDirProc(void) {
	if (g_nparams > 2) {
		printf("Too many arguments!..\n\n");
		return;
	}
	if (g_nparams == 1) { //cd tek başına kullanılmıştır
		printf("%s\n\n", g_cwd);
		return;
	}
	if (!SetCurrentDirectory(g_params[1])) {
		printf("Directory not found or cannot change: %s\n\n", g_params[1]);
		return;
	}

	if (!GetCurrentDirectory(MAX_PATH, g_cwd)) //Yeni dizini yazdır
		ExitSys("GetCurrentDirectory");
}

void DispDirectory(LPCTSTR lpszPath) {
	WIN32_FIND_DATA wfd;
	char lpszDirPath[MAX_PATH];
	HANDLE hFF;

	sprintf(lpszDirPath, "%s/*.*", lpszPath);

	if ((hFF = FindFirstFile(lpszDirPath, &wfd)) == INVALID_HANDLE_VALUE) {
		printf("directory not found or cannot display!\n\n");
		return;
	}

	do {
		if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			printf("%-10s", "<DIR>");
		else
			printf("%-10lu", wfd.nFileSizeLow);

		printf("%s\n", wfd.cFileName);
	} while (FindNextFile(hFF, &wfd));

	printf("\n");
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
