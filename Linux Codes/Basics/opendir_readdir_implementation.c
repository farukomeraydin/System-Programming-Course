#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>

void exit_sys(const char *msg);

int main (int argc, char* argv[]){
    DIR* dir;
    struct dirent *dent;

    if (argc != 2){
        fprintf(stderr, "wrong number of arguments!..\n");
        exit(EXIT_FAILURE);
    }

    if ((dir = opendir(argv[1])) == NULL)
        exit_sys("opendir");


    while (errno = 0, (dent = readdir(dir)) != NULL)
        printf("%s\n", dent->d_name);
        
    
    
    if (errno != 0)
        exit_sys("readdir");

    closedir(dir);

    return 0;
}


void exit_sys(const char *msg)
{
	perror(msg);

	exit(EXIT_FAILURE);
}
