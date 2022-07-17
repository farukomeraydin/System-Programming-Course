#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

int main (int argc, char* argv[]){
	int i;
	unsigned int omode;
	mode_t modes[] = {S_IRUSR, S_IWUSR, S_IXUSR, S_IRGRP, S_IWGRP, S_IXGRP, S_IROTH, S_IWOTH, S_IXOTH};
	mode_t mode;

	if (argc < 3){
		fprintf(stderr, "wrong number of arguments!..\n");
		exit(EXIT_FAILURE);
	}
	if (strlen(argv[1]) > 3){
		fprintf(stderr, "permissions must have maximum 3 octal digits!..\n");
		exit(EXIT_FAILURE);
	}

	for (i = 0; argv[1][i] != '\0'; ++i)
		if (argv[1][i] < '0' || argv[1][i] > '7'){
			fprintf(stderr, "invalid octal digits!..\n");
			exit(EXIT_FAILURE);
		}

	sscanf(argv[1], "%o", &omode);
	mode = 0;

	for (i = 0; i < 9; ++i)
		mode |= (omode >> (8 - i) & 1) ? modes[i] : 0;
	
	for (i = 2; i < argc; ++i){
		if (chmod(argv[i], mode) == -1){
			fprintf(stderr, "%s: %s\n", argv[i], strerror(errno));
		}
	}

    return 0;
}
