#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* mystrtok(const char* str, const char* delim) {
    static const char* pos;
    const char* beg;
    char* dstr;

    if (str != NULL)
        pos = str;

    while (*pos != '\0' && strchr(delim, *pos) != NULL)
        ++pos;

    if (*pos == '\0')
        return NULL;

    beg = pos;

    while (*pos != '\0' && strchr(delim, *pos) == NULL)
        ++pos;

    if ((dstr = (char*)malloc(pos - beg + 1)) == NULL) //using malloc is not a good method
        return NULL;
    //User must free the memory himself

    strncpy(dstr, beg, pos - beg);
    dstr[pos - beg] = '\0';

    return dstr;
}

int main(void)
{
    char text[] = "10/12/2009";
    char* pstr;

    for (pstr = mystrtok(text, "/"); pstr != NULL; pstr = mystrtok(NULL, "/")) {
        puts(pstr); //or puts(str)
        free(pstr);
    }

    return 0;
}
