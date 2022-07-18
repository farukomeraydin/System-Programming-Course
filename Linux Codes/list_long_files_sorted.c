#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
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
#define BLOCK_SIZE    32

struct lsinfo {
	struct stat finfo;
	char* name;
};

void exit_sys(const char* msg);
const char* get_ls(const struct lsinfo* lsinfo, int hlink_digit, int uname_digit, int gname_digit, int size_digit);
int cmp_name(const void* pv1, const void* pv2);

int main(int argc, char* argv[])
{
	DIR* dir;
	struct dirent* dent;
	struct lsinfo* lsinfo;
	int count;
	char path[MAX_PATH];
	struct passwd* pass;
	struct group* gr;
	int len;
	int hlink_digit, uname_digit, gname_digit, size_digit;
	int i;

	if (argc != 2) {
		fprintf(stderr, "wrong number of arguments!..\n");
		exit(EXIT_FAILURE);
	}

	if ((dir = opendir(argv[1])) == NULL)
		exit_sys("open");

	lsinfo = NULL;
    /*All the files in directory dynamically allocated and assigned to finfo stat struct array*/

	for (count = 0, errno = 0; (dent = readdir(dir)) != NULL; ++count) {
		sprintf(path, "%s/%s", argv[1], dent->d_name);
		if (count % BLOCK_SIZE == 0)
			if ((lsinfo = realloc(lsinfo, (count + BLOCK_SIZE) * sizeof(struct lsinfo))) == NULL) {
				fprintf(stderr, "cannot allocate memory!..\n");
				exit(EXIT_FAILURE);
			}
		if ((lsinfo[count].name = (char*)malloc(strlen(dent->d_name) + 1)) == NULL) { //Dynamic allocation for names
			fprintf(stderr, "cannot allocate memory!..\n");
			exit(EXIT_FAILURE);
		}
		strcpy(lsinfo[count].name, dent->d_name);
		if (stat(path, &lsinfo[count].finfo) == -1)
			exit_sys("stat");
	}

	if (errno != 0)
		exit_sys("readdir");

	closedir(dir);
    /*Now we have stat info for each files*/
	hlink_digit = uname_digit = gname_digit = size_digit = 0;
    /*We find the longest column*/
	for (i = 0; i < count; ++i) {
		len = (int)log10(lsinfo[i].finfo.st_nlink) + 1;
		if (len > hlink_digit)
			hlink_digit = len;

		if ((pass = getpwuid(lsinfo[i].finfo.st_uid)) == NULL)
			exit_sys("getppuid");

		len = (int)strlen(pass->pw_name);
		if (len > uname_digit)
			uname_digit = len;

		if ((gr = getgrgid(lsinfo[i].finfo.st_gid)) == NULL)
			exit_sys("getgrgid");

		len = (int)strlen(gr->gr_name);
		if (len > gname_digit)
			gname_digit = len;

		len = (int)log10(lsinfo[i].finfo.st_size) + 1;
		if (len > size_digit)
			size_digit = len;
	}

	qsort(lsinfo, count, sizeof(struct lsinfo), cmp_name); //Names are sorted

	for (i = 0; i < count; ++i)
		printf("%s\n", get_ls(&lsinfo[i], hlink_digit, uname_digit, gname_digit, size_digit));

	for (i = 0; i < count; ++i)
		free(lsinfo[i].name);
	free(lsinfo);

	return 0;
}

const char* get_ls(const struct lsinfo* lsinfo, int hlink_digit, int uname_digit, int gname_digit, int size_digit)
{
	static char buf[4096];
	static mode_t modes[] = { S_IRUSR, S_IWUSR, S_IXUSR, S_IRGRP, S_IWGRP, S_IXGRP, S_IROTH, S_IWOTH, S_IXOTH };
	struct passwd* pass;
	struct group* gr;
	int index = 0;
	int i;

	if (S_ISREG(lsinfo->finfo.st_mode))
		buf[index] = '-';
	else if (S_ISDIR(lsinfo->finfo.st_mode))
		buf[index] = 'd';
	else if (S_ISCHR(lsinfo->finfo.st_mode))
		buf[index] = 'c';
	else if (S_ISBLK(lsinfo->finfo.st_mode))
		buf[index] = 'b';
	else if (S_ISFIFO(lsinfo->finfo.st_mode))
		buf[index] = 'p';
	else if (S_ISLNK(lsinfo->finfo.st_mode))
		buf[index] = 'l';
	else if (S_ISSOCK(lsinfo->finfo.st_mode))
		buf[index] = 's';
	++index;

	for (i = 0; i < 9; ++i)
		buf[index++] = (lsinfo->finfo.st_mode & modes[i]) ? "rwx"[i % 3] : '-';
	buf[index] = '\0';

	index += sprintf(buf + index, " %*llu", hlink_digit, (unsigned long long)lsinfo->finfo.st_nlink);

	if ((pass = getpwuid(lsinfo->finfo.st_uid)) == NULL)
		return NULL;
	index += sprintf(buf + index, " %-*s", uname_digit, pass->pw_name);

	if ((gr = getgrgid(lsinfo->finfo.st_gid)) == NULL)
		return NULL;
	index += sprintf(buf + index, " %-*s", gname_digit, gr->gr_name);

	index += sprintf(buf + index, " %*lld", size_digit, (long long)lsinfo->finfo.st_size);
	index += strftime(buf + index, 100, " %b %e %H:%M", localtime(&lsinfo->finfo.st_mtime));

	sprintf(buf + index, " %s", lsinfo->name);

	return buf;
}

int istrcmp(const char* s1, const char* s2) {
	while (tolower(*s1) == tolower(*s2)) {
		if (*s1 == '\0')
			return 0;
		++s1;
		++s2;
	}
	return tolower(*s1) - tolower(*s2);
}

int cmp_name(const void* pv1, const void* pv2) {
	const struct lsinfo* lsinfo1 = (const struct lsinfo*)pv1;
	const struct lsinfo* lsinfo2 = (const struct lsinfo*)pv2;

	return istrcmp(lsinfo1->name, lsinfo2->name);
}

void exit_sys(const char* msg)
{
	perror(msg);

	exit(EXIT_FAILURE);
}
