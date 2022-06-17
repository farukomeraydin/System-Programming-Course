#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

int main(int argc, char* argv[]){
    int result;
    int a_flag, b_flag, c_flag, h_flag, line_flag;
    char* b_arg,  *c_arg, *line_arg;
    int err_flag;
    int i;
    struct option options[] = {
        {"help", no_argument,NULL, 'h'},
        {"count", required_argument,NULL, 'c'},
        {"line", optional_argument,NULL, 3},
        {0, 0, 0, 0},
    };

    opterr = 0;

    a_flag = b_flag = h_flag = c_flag = line_flag = 0;
    err_flag = 0;

    while((result = getopt_long(argc, argv, "ab:c:h", options, NULL)) != -1){
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
                c_arg = optarg;
                break;
            case 'h':
                h_flag = 1;
                break;
            case 3:   /*--line*/
                line_flag = 1;
                line_arg = optarg;
                break;
            case '?':
                if (optopt == 'b')
                    fprintf(stderr, "-b option must have an argument!..\n");
                else if (optopt == 2) //count option must have an argument
                    fprintf(stderr, "argument must be specified with --count option\n"); //Does not give wrong long option
                else if (optopt == 'c')
                    fprintf(stderr, "-c or --count option must have an argument!..\n");
                else if (optopt != 'c')
                    fprintf(stderr, "Invalid option: -%c\n", optopt);
                else
                    fprintf(stderr, "Invalid long option!..\n");

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
        printf("-c or --count option specified with \"%s\"\n", c_arg);

    if (h_flag)
        printf("--h or --help option used..\n");

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
