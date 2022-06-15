#include <stdio.h>
#include <string.h>

int main(void)
{
    char s[] = "12/11/2009";
    char* pstr;

    
    for (pstr = strtok(s, "/"); pstr != NULL; pstr = strtok(NULL, "/"))
        puts(pstr);

    return 0;
}
