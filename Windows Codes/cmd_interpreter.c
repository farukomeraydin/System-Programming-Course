#include <stdio.h>
#include <string.h>

#define PROMPT			"CSD>"
#define MAX_CMD_LINE	4096
#define MAX_CMD_PARAMS	64

struct CMD {
	char* cmd_text;
	void (*proc)(void);
};

void parse_cmd_line(void);
void proc_dir(void);
void proc_copy(void);
void proc_cls(void);
void proc_rename(void);

char g_cmd_line[MAX_CMD_LINE];
struct CMD g_cmds[] = {
	{"dir", proc_dir},
	{"copy", proc_copy},
	{"cls", proc_cls},
	{"rename", proc_rename},
	//You can add new elements without changing the code
	{NULL, NULL},
};
char* g_params[MAX_CMD_PARAMS];
int g_nparams;

int main(void) {
	char* str;
	int i;

	for (;;) {
		printf(PROMPT);
		fgets(g_cmd_line, MAX_CMD_LINE, stdin); //gets new line too.
		if ((str = strchr(g_cmd_line, '\n')) != NULL)
			*str = '\0';

		parse_cmd_line();
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

void parse_cmd_line(void) {
	char* str;

	g_nparams = 0;
	for (str = strtok(g_cmd_line, " \t"); str != NULL; str = strtok(NULL, " \t"))
		g_params[g_nparams++] = str;
	g_params[g_nparams] = NULL;
}
void proc_dir(void) {
	printf("dir command\n");
}

void proc_copy(void) {
	if (g_nparams != 3) {
		printf("wrong number of arguments!..\n\n");
		return;
	}
}

void proc_cls(void) {
	if (g_nparams != 1) {
		printf("too many arguments!..\n\n");
		return;
	}

	printf("cls command\n");
}

void proc_rename(void) {
	printf("rename command\n");
}
