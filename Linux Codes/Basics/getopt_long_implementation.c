#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

int main(int argc, char* argv[]){
    int result, index;
    int a_flag, b_flag, c_flag, help_flag, count_flag, line_flag;
    char* b_arg,  *count_arg, *line_arg;
    int err_flag;
    int i;
    struct option options[] = {
        {"help", no_argument,&help_flag, 1},
        {"count", required_argument,NULL, 2},
        {"line", optional_argument,NULL, 3},
        {0, 0, 0, 0},
    };

    opterr = 0;

    a_flag = b_flag = c_flag = help_flag = count_flag = line_flag = 0;
    err_flag = 0;

    while((result = getopt_long(argc, argv, "ab:c", options, &index)) != -1){
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
            case 2:   /*--count*/
                count_flag = 1;
                count_arg = optarg;
                break;
            case 3:   /*--line*/
                line_flag = 1;
                line_arg = optarg;
                break;
            case '?':
                if (optopt == 'b')
                    fprintf(stderr, "-b option must have an argument!..\n");
                else if (optopt == 2) //count option must have an argument
                    fprintf(stderr, "argument must be specified with --count option\n"); //optopt doesn't give wrong long option argument
                else
                    fprintf(stderr, "Invalid switch!..\n");

                err_flag = 1;
                break;
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

    if (help_flag)
        printf("--help option used..\n");

    if (count_flag)
        printf("--count option specified with \"%s\"\n", count_arg);

    if (line_flag){
        if (line_arg != NULL)
            printf("--line option used with optional argument \"%s\"\n", line_arg);
        else
            printf("--line option used without optional argument..\n");
    }

    if (optind != argc){
        printf("Arguments without options:\n");
        for(i = optind; i < argc; ++i)
            printf("%s\n", argv[i]);
    }
    return 0;
}
