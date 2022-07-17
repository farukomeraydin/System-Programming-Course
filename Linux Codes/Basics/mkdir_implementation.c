#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <getopt.h>

void exit_sys(const char *msg);


int main (int argc, char* argv[]){
	int i, result;
	unsigned int omode;
	mode_t modes[] = {S_IRUSR, S_IWUSR, S_IXUSR, S_IRGRP, S_IWGRP, S_IXGRP, S_IROTH, S_IWOTH, S_IXOTH};
	mode_t mode;
    int m_flag, err_flag;
    char* m_arg;
    struct option options[] = {
        {"mode", required_argument, NULL, 'm'},
        {0, 0, 0, 0},
    };

    opterr = 0;

    m_flag = 0;
    err_flag = 0;

    while((result = getopt_long(argc, argv, "m:", options, NULL)) != -1){
        switch(result){
            case 'm':
                m_flag = 1;
                m_arg = optarg;
                break;
            case '?':
                if (optopt == 'm')
                    fprintf(stderr, "-m option must have an argument!..\n");
                else if (optopt != 0) 
                    fprintf(stderr, "invalid option: -%c\n", optopt); //optopt does not give wrong long option
                else
                    fprintf(stderr, "Invalid long option!..\n");

                err_flag = 1;	
        }
    }
    if (err_flag)
        exit(EXIT_FAILURE);

    if (m_flag){
        if (strlen(m_arg) > 3){
            fprintf(stderr, "mode must have maximum 3 octal digits!..\n");
            exit(EXIT_FAILURE);
        }
    

        for (i = 0; m_arg[i] != '\0'; ++i)
            if (m_arg[i] < '0' || m_arg[i] > '7'){
                fprintf(stderr, "invalid octal digits!..\n");
                exit(EXIT_FAILURE);
            }
        sscanf(m_arg, "%o", &omode);
        mode = 0;

        for (i = 0; i < 9; ++i)
            mode |= (omode >> (8 - i) & 1) ? modes[i] : 0;
    }
    else
        mode = S_IRWXU | S_IRWXG | S_IRWXO; //default mode
	
    umask(0); //We need to reset umask so function does not get affected.

	for (i = optind; i < argc; ++i)
		if (mkdir(argv[i], mode) == -1)
			fprintf(stderr, "%s: %s\n", argv[i], strerror(errno));


    return 0;
}
void exit_sys(const char *msg)
{
	perror(msg);

	exit(EXIT_FAILURE);
}
