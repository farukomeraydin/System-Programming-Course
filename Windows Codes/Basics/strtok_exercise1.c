#include <stdio.h>
#include <string.h>

int main(void)
{
    char s[] = "   Ali,    Veli, Selami    ";
    char* pstr;

    pstr = strtok(s, ", ");
    while (pstr != NULL) {
        puts(pstr);
        pstr = strtok(NULL, ", ");
    }

    return 0;
}
