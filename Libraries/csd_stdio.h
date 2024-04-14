#ifndef CSD_STDIO_H_
#define CSD_STDIO_H_

#define CSD_EOF             -1
#define CSD_BUFSIZ          5

#include <sys/types.h>

typedef struct{
    int fd;
    unsigned char* beg; /*starting buffer address*/
    size_t size;    /*Buffer size*/
    size_t count;   /*Number of bytes in buffer*/
    unsigned char* pos;     /*Current buffer address*/
    off_t offset;       /*File offset*/
    int dirty;
    int error;
    int eof;
} CSD_FILE;

CSD_FILE* csd_fopen(const char* path, const char* mode);
int csd_fgetc(CSD_FILE* f);
int csd_ferror(CSD_FILE* f);

#endif
