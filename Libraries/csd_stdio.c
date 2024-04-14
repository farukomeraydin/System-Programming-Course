#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "csd_stdio.h"

static ssize_t refresh_buffer(CSD_FILE* f);

CSD_FILE* csd_fopen(const char* path, const char* mode){

    CSD_FILE* f;
    int i;
    static char* modes[] = {"r", "r+", "w", "w+", "a", "a+", "rb", "r+b", "wb", "w+b", "ab", "a+b", NULL};
    static int flags[] = {O_RDONLY, O_RDWR, O_WRONLY | O_CREAT | O_TRUNC, O_RDWR | O_CREAT | O_TRUNC, O_WRONLY | O_CREAT | O_APPEND, O_WRONLY | O_CREAT | O_APPEND, O_WRONLY | O_CREAT | O_APPEND};

    if ((f = (CSD_FILE*)malloc(sizeof(CSD_FILE))) == NULL)
        return NULL;

    for (i = 0; modes[i] != NULL; ++i)
        if (!strcmp(mode, modes[i]))
            break;

    if (modes[i] == NULL){
        free(f);
        return NULL;
    }

    if ((f-> fd = open(path, flags[i % 6], S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1){
        free(f);
        return NULL;
    }

    if ((f -> beg = (unsigned char*)malloc(CSD_BUFSIZ)) == NULL){
        free(f);
        return NULL;
    }

    /*Henüz tamponda bir şey yok*/
    f -> size = CSD_BUFSIZ;
    f -> count = 0;
    f -> pos = NULL;
    f -> offset = 0;
    f -> dirty = 0;
    f -> error = 0;

    return f;

}

static ssize_t refresh_buffer(CSD_FILE* f){
    ssize_t result;

    if (f -> dirty){
        if (lseek(f->fd, f->offset, SEEK_SET) == -1)
            return -1;

        if (write(f->fd, f->beg, f->pos - f->beg) == -1)
            return -1;
    }

    if (lseek(f->fd, f->offset + f->count, SEEK_SET) == -1)
            return -1;

    if ((result = read(f->fd, f->beg, f->size)) == -1)
        return -1;

    
    f->pos = f->beg;
    f->offset = f->offset + f->count;
    f->count = result;

    return result;
}

int csd_fgetc(CSD_FILE* f) {
    ssize_t result;

    if (f->pos == NULL || f->pos == f->beg + f->count){
        if ((result = refresh_buffer(f)) == -1){
            f -> error = 1;
            return CSD_EOF;
        }

        if (result == 0){
            f->eof = 1;
            return CSD_EOF;
        }
    }

    return *f->pos++;
}

int csd_ferror(CSD_FILE* f){
    return f -> error;
}
