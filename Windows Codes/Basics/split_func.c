#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** split(char* str, const char* delim);
int main(void) {
    char names[] = "10/12/1990";
    char** str;
    int i;

    if ((str = split(names, "/")) == NULL) {
        fprintf(stderr, "cannot split!..\n");
        exit(EXIT_FAILURE);
    }

    for (i = 0; str[i] != NULL; ++i)
        puts(str[i]);

    free(str);
    return 0;
}
char** split(char* str, const char* delim) {
    char* s;
    char** tokens = NULL, ** temp;
    int i;

    for (i = 0, s = strtok(str, delim); s != NULL; s = strtok(NULL, delim), ++i)
    {
        /*If realloc is unsuccessful, we assign it to temp, therefore tokens are not corrupted*/
        if ((temp = (char**)realloc(tokens, sizeof(char*) * (i + 2))) == NULL) {
            free(tokens);
            return NULL;
        }
        tokens = temp;
        tokens[i] = s;
    }
    tokens[i] = NULL; //It should point to NULL at the end


    return tokens;
}
