#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    FILE *f;
    int ch;
    clock_t t1, t2;
    double ts;

    t1 = clock();

    if ((f = fopen("test.dat", "rb")) == NULL) {
        fprintf(stderr, "Cannot open file!..\n");
        exit(EXIT_FAILURE);
    }

    while ((ch = fgetc(f)) != EOF)
        ;

    fclose(f);

    t2 = clock();

    ts = (double)(t2 - t1) / CLOCKS_PER_SEC;

    printf("Elapsed time: %f\n", ts);

    return 0;

}
