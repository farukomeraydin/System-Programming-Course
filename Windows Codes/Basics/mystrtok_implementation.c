#include <stdio.h>
#include <string.h>

char* mystrtok(char* str, const char* delim) {
    static char* pos;
    char* beg;

    if (str != NULL)
        pos = str;

    while (*pos != '\0' && strchr(delim, *pos) != NULL)
        ++pos;

    if (*pos == '\0')
        return NULL;

    beg = pos;

    while (*pos != '\0' && strchr(delim, *pos) == NULL)
        ++pos;

    if (*pos != '\0')
        *pos++ = '\0';

    return beg;
}

int main(void)
{
    char s[] = ",,,,,,Ali,,,,,,Veli,,,,,,,,Selami,,,";
    char* pstr;

    for (pstr = mystrtok(s, ","); pstr != NULL; pstr = mystrtok(NULL, ","))
        puts(pstr);

    return 0;
}
