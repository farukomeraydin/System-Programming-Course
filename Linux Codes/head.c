#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

void write_lines(FILE* f, int nlines);
void write_chars(FILE* f, int nchars);

int main(int argc, char* argv[]){

    int result;
    int c_flag, n_flag, v_flag, help_flag, version_flag, err_flag;
    const char* c_arg, *n_arg;
    int i, nlines, nchars;
    FILE* f;

    struct option options[] = {
        {"bytes", required_argument, NULL, 'c'},
        {"line", required_argument, NULL, 'n'},
        {"verbose", no_argument, NULL, 'v'},
        {"help", no_argument, NULL, 1},
        {"version", no_argument, NULL, 2},
        { 0, 0, 0, 0}
    };
    
    opterr = 0;
    c_flag = n_flag = v_flag = help_flag = version_flag = 0;
    err_flag = 0;

    while ((result = getopt_long(argc, argv, "c:n:v", options, NULL)) != -1){
      switch (result)
      {
        case 'c':
            c_flag = 1;
            c_arg = optarg;
            break;
        case 'n':
            n_flag = 1;
            n_arg = optarg;
            break;
        case 'v':
            v_flag = 1;
            break;
        case 1:
            help_flag = 1;
            break;
        case 2:
            version_flag = 2;
            break;
        case '?':
            switch(optopt){
                case 'c':
                    fprintf(stderr, "-c or --bytes must have argument!..\n");
                    break;
                case 'n':
                    fprintf(stderr, "-n or --line must have argument!..\n");
                    break;
                default:
                    if (optopt != 0)
                        fprintf(stderr, "invalid option: -%c\n", optopt);
                    else
                        fprintf(stderr, "invalid long option!..\n");
            }
            err_flag = 1;
            break;
      }  
    }
    if (err_flag)
        exit(EXIT_FAILURE);

    if (help_flag){
        if(c_flag || n_flag || v_flag || version_flag){
            fprintf(stderr, "--help option must not be used with other options!..\n");
            exit(EXIT_FAILURE);
        }
        printf("Usage: head [OPTION]... [FILE]...\n");
        exit(EXIT_SUCCESS);
    }

    if (version_flag){
        if(c_flag || n_flag || v_flag || help_flag){
            fprintf(stderr, "--version option must not be used with other options!..\n");
            exit(EXIT_FAILURE);
        }
        printf("1.0\n");
        exit(EXIT_SUCCESS);
    }   
 
    
    if (n_flag && c_flag){
        fprintf(stderr, "-n (--line) and -c (--bytes) options cannot be used together!..\n");
        exit(EXIT_FAILURE);
    }
    
    if (optind == argc){
        fprintf(stderr, "at least one file must be specified!..\n");
        exit(EXIT_FAILURE);
    }

    if (argc - optind > 1)
        v_flag = 1; //If more than 1 file is entered, there will be verbose
    
    if (n_flag)
        nlines = (int)strtol(n_arg, NULL, 10);
    else if (c_flag)
        nchars = (int)strtol(c_arg, NULL, 10);
    else{
        n_flag = 1;
        nlines = 10;
    }


    for (i = optind; i < argc; ++i)
    {
        if ((f = fopen(argv[i], "r")) == NULL){
            fprintf(stderr, "file not found or cannot open: %s\n", argv[i]);
            continue;
        }
        if (v_flag)
            printf("==> %s <==\n", argv[i]);
        if (n_flag)
            write_lines(f, nlines);
        else if (c_flag)
            write_chars(f, nchars);
    }

    return 0;
}

void write_lines(FILE* f, int nlines){
    int ch;
    int n = 0;
    while ((ch = fgetc(f)) != EOF && n < nlines){
        putchar(ch);
        if (ch == '\n')
            ++n;
    }
    if (ferror(f))
        fprintf(stderr, "cannot read file!..\n");
}
void write_chars(FILE* f, int nchars){
    int ch;
    int i;
    for (i = 0; i < nchars && (ch = fgetc(f)) != EOF; ++i)
        putchar(ch);

    if (ferror(f))
        fprintf(stderr, "cannot read file!..\n");
    putchar('\n');
}
