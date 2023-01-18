/*
In Windows systems max path is specified with MAX_PATH macro.However, in POSIX systems there is no macro like this but during run time we can
obtain max path.We showed the function that obtains that below.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

void exit_sys(const char* msg);

long path_max(void){
	static long result = 0;

#define PATH_MAX_INDETERMINATE_GUESS	4096

#ifdef PATH_MAX
	result = PATH_MAX;
#else
	if (result == 0){
		errno = 0;
		if ((result = pathconf("/", _PC_PATH_MAX)) == -1 && errno == 0)
			result = PATH_MAX_INDETERMINATE_GUESS;
	}
#endif

	return result;
}



int main(void){
	char* cwd; //stack yetersiz ise static anahtar sözcüğünü kullan.
	long size;
	size = path_max();

	if ((cwd = (char*)malloc(size)) == NULL)
		exit_sys("malloc"); //POSIX sistemlerde malloc errnoyu set ettiği için böyle kullanabilirsin.

	if (getcwd(cwd, 4096) == NULL)
		exit_sys("getcwd");

	printf("size: %ld, cwd = %s\n", size, cwd);

	free(cwd);

	return 0;
}

void exit_sys(const char* msg){
	perror(msg);
	exit(EXIT_FAILURE);
}
