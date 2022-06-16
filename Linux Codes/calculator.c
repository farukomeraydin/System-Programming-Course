#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]){
    int result;
    int a_flag, s_flag, m_flag, d_flag;
    int err_flag;
    double arg1, arg2, val_result;

    opterr = 0;

    a_flag = s_flag = m_flag = d_flag = 0;
    err_flag = 0;

    while((result = getopt(argc, argv, "asmd")) != -1){
        switch(result){
            case 'a':
                a_flag = 1;
                break;
            case 's':
                s_flag = 1;
                break;
            case 'm':
                m_flag = 1;
                break;
            case 'd':
                d_flag = 1;
                break;
            case '?':
                fprintf(stderr, "invalid option:-%c\n", optopt);
                err_flag = 1;
        }
    }

    if (err_flag)
        exit(EXIT_FAILURE);

    if (a_flag + s_flag + m_flag + d_flag != 1){
        fprintf(stderr, "Exactly 1 option must be specified!\n");
        exit(EXIT_FAILURE);
    }

    if (argc - optind != 2){
        fprintf(stderr, "wrong number of arguments!..\n");
        exit(EXIT_FAILURE);
    }

    arg1 = strtod(argv[optind], NULL);
    arg2 = strtod(argv[optind + 1], NULL);

    if (a_flag)
        val_result = arg1 + arg2;
    else if (s_flag)
        val_result = arg1 - arg2;
    else if (m_flag)
        val_result = arg1 * arg2;
    else
        val_result = arg1 / arg2;

    printf("%f\n", val_result);
    return 0;
}
