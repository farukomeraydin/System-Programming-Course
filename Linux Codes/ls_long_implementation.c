#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>

const char* getls_mode(mode_t mode);

int main (int argc, char* argv[]){
    struct stat finfo;
    int i;
    struct passwd* pwd;
    struct group *grp;

	if (argc == 1){
        fprintf(stderr, "wrong number of arguments!..\n");
        exit(EXIT_FAILURE);
    }

    for (i = 1; i < argc; ++i){
        if (stat(argv[i], &finfo) == -1){
            fprintf(stderr, "stat: %s\n", strerror(errno));
			continue;
		}

        pwd = getpwuid(finfo.st_uid);
        grp = getgrgid(finfo.st_gid);

        printf("---------------------------------------\n");
        printf("%s\n\n", argv[i]);
        printf("Mode: %s\n", getls_mode(finfo.st_mode));
        printf("%-20s%lld\n", "Size", (long long)finfo.st_size);
        printf("%-20s%llu\n", "I-Node", (unsigned long long)finfo.st_ino);
        printf("%-20s%s(%lld)\n", "User id", pwd ? pwd->pw_name : "?????", (long long)finfo.st_uid);
        printf("%-20s%s(%lld)\n", "Group id", grp ? grp->gr_name : "?????", (long long)finfo.st_gid);
        printf("%-20s%s", "Last Update", ctime(&finfo.st_mtime));
        printf("%-20s%s", "Last Read", ctime(&finfo.st_atime));
        printf("%-20s%s", "Last I-Node Update", ctime(&finfo.st_ctime));
    }

    return 0;
}
const char* getls_mode(mode_t mode){
    static char tmode[11]; //length of -rwxrwxrwx is 11
    mode_t modef[] = {S_IRUSR, S_IWUSR, S_IXUSR, S_IRGRP, S_IWGRP, S_IXGRP, S_IROTH, S_IWOTH, S_IXOTH};
    char* modec = "rwx";
    int i;

    if(S_ISREG(mode)) //or mode & S_ISREG
        tmode[0] = '-';
    else if (S_ISDIR(mode))
        tmode[0] = 'd';
    else if (S_ISCHR(mode))
        tmode[0] = 'c';
    else if (S_ISBLK(mode))
        tmode[0] = 'b';
    else if (S_ISFIFO(mode))
        tmode[0] = 'p';
    else if (S_ISLNK(mode))
        tmode[0] = 'l';
    else if (S_ISSOCK(mode))
        tmode[0] = 's';

    for (i = 0; i < 9; ++i)
        tmode[i + 1] = mode & modef[i] ? modec[i % 3] : '-';

    tmode[i + 1] = '\0'; //This is not necessary because static object initialized with null character
    return tmode;
}
