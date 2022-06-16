#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]){
    int result;
    int a_flag, b_flag, c_flag;
    char* b_arg;
    int i, err_flag;

    opterr = 0;

    a_flag = b_flag = c_flag = 0;
    err_flag = 0;

    while((result = getopt(argc, argv, "ab:c")) != -1){
        switch(result){
            case 'a':
                a_flag = 1;
                break;
            case 'b':
                b_flag = 1;
                b_arg = optarg;
                break;
            case 'c':
                c_flag = 1;
                break;
            case '?':
                fprintf(stderr, "invalid option:-%c\n", optopt);
                err_flag = 1;
        }
    }

    if (err_flag)
        exit(EXIT_FAILURE);

    if (a_flag)
        printf("-a option used..\n");

    if (b_flag)
        printf("-b option used with argument \"%s\"\n", b_arg);
    

    if (c_flag)
        printf("-c option used..\n");

    if (optind != argc){
        printf("Argument without options:\n");
        for(i = optind; i < argc; ++i)
            printf("%s\n", argv[i]);
    }
    return 0;
}
