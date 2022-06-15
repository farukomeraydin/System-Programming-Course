#include <stdio.h>
#include <string.h>

char* mystrtok(const char* str, const char* delim, char* dest) {
    static const char* pos;
    const char* beg;

    if (str != NULL)
        pos = str;

    while (*pos != '\0' && strchr(delim, *pos) != NULL)
        ++pos;

    if (*pos == '\0')
        return NULL;

    beg = pos;

    while (*pos != '\0' && strchr(delim, *pos) == NULL)
        ++pos;

    strncpy(dest, beg, pos - beg); //strcpy is not used because there is no null character
    dest[pos - beg] = '\0';

    return dest;
}

int main(void)
{
    char text[] = "10/12/2009";
    char str[100];
    char* pstr;

    for (pstr = mystrtok(text, "/", str); pstr != NULL; pstr = mystrtok(NULL, "/", str))
        puts(pstr); //or puts(str)

    return 0;
}
