#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <dirent.h>

void exit_sys(const char *msg);

int mycallback(const struct dirent* de){
	if (tolower(de->d_name[0]) == 'a')
		return 1;

	return 0;
}

int main()
{
	struct dirent** dents;
	int i, count;
	if ((count = scandir("/usr/include", &dents, mycallback, NULL)) == -1)
		exit_sys("scandir");

	for (i = 0; i < count; ++i)
		printf("%s\n", dents[i]->d_name);

	for (i = 0; i < count; ++i)
		free(dents[i]);
	
	free(dents);
	
	return 0;
}

void exit_sys(const char *msg)
{
	perror(msg);

	exit(EXIT_FAILURE);
}
