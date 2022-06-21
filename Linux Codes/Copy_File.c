//(./mycp [-i-n][--interactive --no-clobber] <source path> <destination path>)
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <getopt.h>

#define BUF_SIZE    8192

void exit_sys(const char *msg);

int main (int argc, char* argv[]){
    int result, index;
    int i_flag, n_flag;
    int err_flag;
    char buf[BUF_SIZE];
    int fds, fdd;
    ssize_t n;

    struct option options[] = {
        {"interactive", no_argument,NULL, 'i'},
        {"no-clobber", no_argument,NULL, 'n'},
        {0, 0, 0, 0},
    };

    opterr = 0;

    i_flag = n_flag = 0;
    err_flag = 0;

    while((result = getopt_long(argc, argv, "in", options, &index)) != -1){
        switch(result){
            case 'i':
                i_flag = 1;
                break;
            case 'n':
                n_flag = 1;
                break;
            case '?':
                if (optopt != 0)
                    fprintf(stderr, "invalid option: -%c\n", optopt);
                else
                    fprintf(stderr, "invalid long option!..\n");
                err_flag = 1;
                break;
        }
    }

    if (err_flag)
        exit(EXIT_FAILURE);

    if (argc - optind != 2){
        fprintf(stderr, "wrong number of arguments!..\n");
        exit(EXIT_FAILURE);
    }

    if (n_flag || i_flag){
        if (access(argv[optind + 1], F_OK) == 0){ //Is file present?
            if (n_flag){
                fprintf(stderr, "file already exists! (-n  specified)\n");
                exit(EXIT_FAILURE);
            }
            if (i_flag){
                printf("file already exists! Overwrite? (Y/N):");
                if (tolower(getchar()) != 'y')
                    exit(EXIT_FAILURE);
            }
        }
    }

    if ((fds = open(argv[optind], O_RDONLY)) == -1)
        exit_sys("open");

    if ((fdd = open(argv[optind + 1], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)) == -1)
        exit_sys("open");    

    while ((n = read(fds, buf, BUF_SIZE)) > 0)
        if (write(fdd, buf, n) == -1) //I/O error
            exit_sys("write");

    if (n == -1)//I/O error
        exit_sys("read");

    close(fds);
    close(fdd);

    return 0;
}

void exit_sys(const char *msg)
{
	perror(msg);

	exit(EXIT_FAILURE);
}
