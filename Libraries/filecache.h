#ifndef FILECACHE_H_
#define FILECACHE_H_

/*Symbolic Constants*/

#define LINE_SIZE            32
#define NCACHE_LINES         5
#define INITIAL_COUNT        5

#ifdef DEBUG
    #define DEBUG_PRINT(fmt, ...) fprintf(stderr, fmt, ## __VA_ARGS__)
#else
    #define DEBUG_PRINT(fmt, ...)
#endif


/*Type Definitions*/

typedef struct tagCACHELINE{
    char buf[LINE_SIZE];
    int blockno;
    size_t count; //count for cache line
} CACHE_LINE;

typedef struct tagCACHE{
    int fd;
    CACHE_LINE clines[NCACHE_LINES];
    size_t tcount;
} CACHE, *HCACHE;

/*Function Prototypes*/

HCACHE open_file(const char *path, int flags);
int read_file(HCACHE hc, int blockno, void *buf);
int close_file(HCACHE hc);

#endif
