#include <stdio.h>

int main(void) {
    char s[] = "777";
    unsigned int x;

    sscanf(s, "%o", &x);
    printf("%x, %d, %o\n", x, x, x);
    return 0;
}
