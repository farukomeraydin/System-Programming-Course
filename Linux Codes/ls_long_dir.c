#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <dirent.h>

#define MAX_PATH      4096

void exit_sys(const char *msg);
const char *get_ls(const char *path, int hlink_digit, int uname_digit, int gname_digit, int size_digit);

int main(int argc, char *argv[])
{
	DIR *dir;
	struct dirent *dent;
	struct stat finfo;
	char path[MAX_PATH];
	struct passwd *pass;
	struct group *gr;
	int len;
	int hlink_digit, uname_digit, gname_digit, size_digit;

	if (argc != 2) {
		fprintf(stderr, "wrong number of arguments!..\n");
		exit(EXIT_FAILURE);
	}

	if ((dir = opendir(argv[1])) == NULL)
		exit_sys("open");

	hlink_digit = uname_digit = gname_digit = size_digit = 0;

	while (errno = 0, (dent = readdir(dir)) != NULL) {
		sprintf(path, "%s/%s", argv[1], dent->d_name);
		if (stat(path, &finfo) == -1)
			exit_sys("stat");

		len = (int)log10(finfo.st_nlink) + 1;
		if (len > hlink_digit)
			hlink_digit = len;

		if ((pass = getpwuid(finfo.st_uid)) == NULL)
			exit_sys("getppuid");

		len = (int)strlen(pass->pw_name);
		if (len > uname_digit)
			uname_digit = len;

		if ((gr = getgrgid(finfo.st_gid)) == NULL)
			exit_sys("getgrgid");

		len = (int)strlen(gr->gr_name);
		if (len > gname_digit)
			gname_digit = len;

		len = (int)log10(finfo.st_size) + 1;
		if (len > size_digit)
			size_digit = len;
	}

	if (errno != 0)
		exit_sys("readdir");

	rewinddir(dir);
	while (errno = 0, (dent = readdir(dir)) != NULL) {
		sprintf(path, "%s/%s", argv[1], dent->d_name);
		if (stat(path, &finfo) == -1)
			exit_sys("stat");

		printf("%s\n", get_ls(path, hlink_digit, uname_digit, gname_digit, size_digit));
	}

	if (errno != 0)
		exit_sys("readdir");

	closedir(dir);

	return 0;
}

const char *get_ls(const char *path, int hlink_digit, int uname_digit, int gname_digit, int size_digit)
{
	struct stat finfo;
	static char buf[4096];
	static mode_t modes[] = { S_IRUSR, S_IWUSR, S_IXUSR, S_IRGRP, S_IWGRP, S_IXGRP, S_IROTH, S_IWOTH, S_IXOTH };
	struct passwd *pass;
	struct group *gr;
	char *str;
	int index = 0;
	int i;

	if (stat(path, &finfo) == -1)
		return NULL;

	if (S_ISREG(finfo.st_mode))
		buf[index] = '-';
	else if (S_ISDIR(finfo.st_mode))
		buf[index] = 'd';
	else if (S_ISCHR(finfo.st_mode))
		buf[index] = 'c';
	else if (S_ISBLK(finfo.st_mode))
		buf[index] = 'b';
	else if (S_ISFIFO(finfo.st_mode))
		buf[index] = 'p';
	else if (S_ISLNK(finfo.st_mode))
		buf[index] = 'l';
	else if (S_ISSOCK(finfo.st_mode))
		buf[index] = 's';
	++index;

	for (i = 0; i < 9; ++i)
		buf[index++] = (finfo.st_mode & modes[i]) ? "rwx"[i % 3] : '-';
	buf[index] = '\0';

	index += sprintf(buf + index, " %*llu", hlink_digit, (unsigned long long)finfo.st_nlink);

	if ((pass = getpwuid(finfo.st_uid)) == NULL)
		return NULL;
	index += sprintf(buf + index, " %-*s", uname_digit, pass->pw_name);

	if ((gr = getgrgid(finfo.st_gid)) == NULL)
		return NULL;
	index += sprintf(buf + index, " %-*s", gname_digit, gr->gr_name);

	index += sprintf(buf + index, " %*lld", size_digit, (long long)finfo.st_size);
	index += strftime(buf + index, 100, " %b %e %H:%M", localtime(&finfo.st_mtime));

	str = strrchr(path, '/');
	sprintf(buf + index, " %s", str ? str + 1 : path);

	return buf;
}

void exit_sys(const char *msg)
{
	perror(msg);

	exit(EXIT_FAILURE);
}
