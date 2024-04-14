#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(void)
{
    FILE *f;

    if ((f = fopen("test.txt", "w")) == NULL) {
        fprintf(stderr, "Cannot open file!..\n");
        exit(EXIT_FAILURE);
    }

    fputc('a', f);
    fputc('b', f);
    fputc('\n', f);

    _exit(0); //Won't flush so characters won't be written

    return 0;
}
