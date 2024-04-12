#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

#define TABSIZE		4

void walkdir_recur(const char* path, int level){
	DIR* dir;
	struct dirent* ent;
	struct stat finfo;

	if ((dir = opendir(path)) == NULL)
		return;

	if (chdir(path) == -1)
		return;

	while ((ent = readdir(dir)) != NULL){
		printf("%*s%s\n", level * TABSIZE, "", ent->d_name);
		if (!strcmp(ent->d_name, ".") || !strcmp(ent->d_name, ".."))
			continue;

		if (lstat(ent->d_name, &finfo) == -1) //lstat gets directory info. Symbolic link doesn't follow.
			continue;

		if (S_ISDIR(finfo.st_mode)){
			walkdir_recur(ent->d_name, level + 1);
			if (chdir("..") == -1)
				break;
		}
	}
	closedir(dir);
}

void walkdir(const char* path){
	char cwd[4096];

	if (getcwd(cwd, 4096) == NULL)
		perror("getcwd");

	walkdir_recur(path, 0);

	if (chdir(cwd) == -1)
		perror("chdir");
}

int main(int argc, char* argv[]){
	
	if (argc != 2){
		fprintf(stderr, "wrong number of arguments!..\n");
		exit(EXIT_FAILURE);
	}
	walkdir(argv[1]);

	return 0;
}
