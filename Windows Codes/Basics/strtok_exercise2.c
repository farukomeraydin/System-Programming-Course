#include <stdio.h>
#include <string.h>

int main(void)
{
    char s[] = "   Ali,    Veli, Selami    ";
    char* pstr;

    for (pstr = strtok(s, ", "); pstr != NULL; pstr = strtok(NULL, ", "))
        puts(pstr);

    return 0;
}
