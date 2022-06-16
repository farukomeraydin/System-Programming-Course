#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHUNK_SIZE  5

char** split(const char* str, const char* delim);
int main(void) {
    char names[] = "ali    , veli   , selami,     ayse ,   fatma,  hüseyin,   sacit";
    char** str;
    int i;

    if ((str = split(names, ", ")) == NULL) {
        fprintf(stderr, "cannot split!..\n");
        exit(EXIT_FAILURE);
    }

    for (i = 0; str[i] != NULL; ++i)
        puts(str[i]);

    for (i = 0; str[i] != NULL; ++i)
        free(str[i]);


    free(str);
    return 0;
}
char** split(const char* str, const char* delim) {
    char* s, * news, * newstr;
    char** tokens = NULL, ** temp;
    int i;

    if ((newstr = (char*)malloc(strlen(str) + 1)) == NULL) //null karakter için de yer ayır
        return NULL;
    strcpy(newstr, str);
    /*Tahsis edilen yeni alanı strtok bozdu*/
    for (i = 0, s = strtok(newstr, delim); s != NULL; s = strtok(NULL, delim), ++i)
    {
        if (i % CHUNK_SIZE == 0) {
            /*Blok blok yer ayırmış olduk*/
            if ((temp = (char**)realloc(tokens, sizeof(char*) * (i + CHUNK_SIZE + 1))) == NULL) {
                free(newstr);
                free(tokens);
                return NULL;
            }
        }
        tokens = temp;

        if ((news = (char*)malloc(strlen(s) + 1)) == NULL) {
            free(newstr);
            free(tokens);
            return NULL;
        }
        strcpy(news, s);
        tokens[i] = news;
    }
    tokens[i] = NULL;
    free(newstr);

    return tokens;
}
