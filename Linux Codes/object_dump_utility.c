#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

/* Symbolic Constants */

#define DEF_LINE                10
#define HEX_OCTAL_LINE_LEN      16

/* Function Prorotypes */

int print_text(FILE *f, int nline);
int print_hex_octal(FILE *f, int nline, int hexflag);

int main(int argc, char *argv[])
{
    int result, err_flag = 0;
    int x_flag = 0, o_flag = 0, t_flag = 0, top_flag = 0, header_flag = 0;
    char *top_arg;
    struct option options[] = {
        {"top", optional_argument, NULL, 1},
        {"header", no_argument, NULL, 'h'},
        {0, 0, 0, 0}
    };
    FILE *f;
    int i, nline = -1;

    opterr = 0;
    while ((result = getopt_long(argc, argv, "xoth", options, NULL)) != -1) {
        switch (result) {
            case 'x':
                x_flag = 1;
                break;
            case 'o':
                o_flag = 1;
                break;
            case 't':
                t_flag = 1;
                break;
            case 'h':
                header_flag = 1;
                break;
            case 1:
                top_flag = 1;
                top_arg = optarg;
                break;
            case '?':
            if (optopt != 0) 
                fprintf(stderr, "invalid switch: -%c\n", optopt);
            else 
                fprintf(stderr, "invalid switch: %s\n", argv[optind - 1]);  /* argv[optind - 1] not documented */
            err_flag = 1;
        }
    }

    if (err_flag)
        exit(EXIT_FAILURE);

    if (x_flag + o_flag + t_flag > 1) {
        fprintf(stderr, "only one option must be specified from -o, -t, -x\n");
        exit(EXIT_FAILURE);
    }
    if (x_flag + o_flag + t_flag == 0)
        t_flag = 1;

    if (top_flag)
        nline = top_arg != NULL ? (int) strtol(top_arg, NULL, 10) : DEF_LINE;

    if (optind == argc)  {
        fprintf(stderr, "at least one file must be specified!..\n");
        exit(EXIT_FAILURE);
    }
 
    for (i = optind; i < argc; ++i) {
        if ((f = fopen(argv[i], "rb")) == NULL) {
            fprintf(stderr, "cannot open file: %s\n", argv[i]);
            continue;
        }

        if (header_flag)
            printf("%s\n\n", argv[i]);

        if (t_flag) 
            result = print_text(f, nline);
        else if (x_flag)
            result = print_hex_octal(f, nline, 1);
        else 
            result = print_hex_octal(f, nline, 0);

        if (i != argc - 1)
            putchar('\n');

        if (!result)
            fprintf(stderr, "cannot read file: %s\n", argv[i]);

        fclose(f);
    }

    return 0;
}

int print_text(FILE *f, int nline)
{
    int ch;
    int count;

    if (nline == -1)
        while ((ch = fgetc(f)) != EOF)
            putchar(ch);
    else {
        count = 0;
        while ((ch = fgetc(f)) != EOF && count < nline) {
            putchar(ch);
            if (ch == '\n')
                ++count;
        }
    }

    return !ferror(f);
}

int print_hex_octal(FILE *f, int nline, int hexflag)
{
    int ch, i, count;
    const char *off_str, *ch_str;

    off_str = hexflag ? "%07X " : "%012o";
    ch_str = hexflag ? "%02X%c" : "%03o%c";

    if (nline == -1)
        for (i = 0; (ch = fgetc(f)) != EOF; ++i) {
            if (i % HEX_OCTAL_LINE_LEN == 0)
                printf(off_str, i);
            printf(ch_str, ch, i % HEX_OCTAL_LINE_LEN == HEX_OCTAL_LINE_LEN - 1 ? '\n' : ' ');
        }
            
    else {
        count = 0;
        for (i = 0; (ch = fgetc(f)) != EOF && count < nline; ++i) {
            if (i % HEX_OCTAL_LINE_LEN == 0)
                printf(off_str, i);
           printf(ch_str, ch, i % HEX_OCTAL_LINE_LEN == HEX_OCTAL_LINE_LEN - 1 ? '\n' : ' ');
            if (ch == '\n')
                ++count;
        }
    }

    if (i % HEX_OCTAL_LINE_LEN != 0)
        putchar('\n');    

    return !ferror(f);
}
