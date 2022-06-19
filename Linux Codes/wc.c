#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <getopt.h>

int main (int argc, char* argv[]){
    int result, index;
    int c_flag, l_flag, L_flag, w_flag, help_flag, version_flag;
    int err_flag;
    int i;
    int lc, wc, cc, lcc, max_lcc, max_cc;
    int ch, flag;
    FILE* f;
    const char *delim = " \t\n.,!*-";

    struct option options[] = {
        {"bytes", no_argument, NULL, 'c'},
        {"lines", no_argument, NULL, 'l'},
        {"max_line_length", no_argument, NULL, 'L'},
        {"words", no_argument, NULL, 'w'},
        {"help", no_argument, NULL, 1},
        {"version", no_argument, NULL, 2},
        {0, 0, 0, 0},
    };

    opterr = 0;

    c_flag = l_flag = L_flag = w_flag = help_flag = version_flag = 0;
    err_flag = 0;

    while((result = getopt_long(argc, argv, "clLw", options, &index)) != -1){
        switch(result){
            case 'c':
                c_flag = 1;
                break;
            case 'l':
                l_flag = 1;
                break;
            case 'L':
                L_flag = 1;
                break;
            case 'w':  
                w_flag = 1;
                break;
            case 1:   /*--help*/
                help_flag = 1;
                break;
            case 2:   /*--version*/
                version_flag = 1;
                break;
            case '?':
                fprintf(stderr, "Invalid option!..\n");
                err_flag = 1;
                break;
        }
    }

    if (err_flag)
        exit(EXIT_FAILURE);

    if (version_flag && (c_flag || l_flag || L_flag || w_flag)){
        fprintf(stderr, "--version must not be used with other options!..\n");
        exit(EXIT_FAILURE);
    }

    if (help_flag && (c_flag || l_flag || L_flag || w_flag)){
        fprintf(stderr, "--version must not be used with other options!..\n");
        exit(EXIT_FAILURE);
    }

    if (help_flag){
        printf("usage: wc [-cwlL][--line, --help, --version] [path list]\n");
        exit(EXIT_FAILURE);
    }

    if (version_flag){
        printf("version 1.0\n");
        exit(EXIT_SUCCESS);
    }

    if (optind == argc){
        fprintf(stderr, "at least one file must be specified!..\n");
        exit(EXIT_FAILURE);
    }

    max_cc = 3;
    for (i = optind; i < argc; ++i){
        if ((f = fopen(argv[i], "r")) == NULL){
            continue; 
        fseek(f, 0, SEEK_END); //File pointer is at the end
        cc = ftell(f); //Gives file pointer's position
        if (cc > max_cc)
            max_cc = cc;
        fclose(f);
    }   
    max_cc = (int)log10(max_cc) + 1;
    if (max_cc < 3)
        max_cc = 3;

    for (i = optind; i < argc; ++i){
        if ((f = fopen(argv[i], "r")) == NULL){ //For word count, read mode
            fprintf(stderr, "file not found or cannot open: %s\n", argv[i]);
            continue; //There might be other files to open
        }
        cc = wc = lc = max_lcc = 0;
        flag = 1;
        lcc = 0;
        while ((ch = fgetc(f)) != EOF){
            ++cc;
            if (ch == '\n'){
                ++lc;
                if (lcc > max_lcc)
                    max_lcc = lcc;
                lcc = 0;
            }
            else
                ++lcc;
            if (strchr(delim, ch) != NULL) //or ch == ' ' || ch == '\n' || ch == '\t'
                flag = 1;
            else if (flag){
                flag = 0;
                ++wc;
            }
        }

        if (l_flag + w_flag + c_flag + L_flag == 0)
            printf("%*d %*d %*d ", max_cc, lc, max_cc, wc, max_cc, cc);
        else{
            if (l_flag)
                printf("%*d ", max_cc, lc);
            if (w_flag)
                printf("%*d ", max_cc, wc);
            if (c_flag)
                printf("%*d ", max_cc, cc);
            if (L_flag)
                printf("%*d ", max_cc, max_lcc);   
        }        
                   printf("%s\n", argv[i]);
    }
    return 0;
}
}
