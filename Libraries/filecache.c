#define DEBUG

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include "filecache.h"

#ifdef DEBUG
static void print_cline_counts(HCACHE hc);
#endif

static size_t select_line(HCACHE hc);

HCACHE open_file(const char *path, int flags){
    HCACHE hc;
    int i;

    if ((hc = (HCACHE)malloc(sizeof(CACHE))) == NULL)
        return NULL;
    
    if ((hc->fd = open(path, flags)) == -1){
        free(hc);
        return NULL;
    }

    for (i = 0; i < NCACHE_LINES; ++i){
        hc->clines[i].blockno = -1;
        hc->clines[i].count = 0;
    }

    return hc;
}

int read_file(HCACHE hc, int blockno, void *buf){
    int i;
    int rline;
    

    for (i = 0; i < NCACHE_LINES; ++i)
        if (hc->clines[i].blockno == blockno){ 
            DEBUG_PRINT("Cache hit block %d, used cache line %d\n", blockno, i);
            memcpy(buf, hc->clines[i].buf, LINE_SIZE);
            ++hc->clines[i].count;
            ++hc->tcount;

            #ifdef DEBUG
            print_cline_counts(hc);
            #endif

            return 0;
        }

    
    rline = select_line(hc); //getting the cacheline that has the least count for replacement.


    if(lseek(hc->fd, (off_t)blockno * LINE_SIZE, SEEK_SET) == -1) //Before reading, file pointer block no should be changed
        return -1;

    if (read(hc->fd, hc->clines[rline].buf, LINE_SIZE) == -1)
        return -1;

    hc->clines[rline].blockno = blockno;

    hc->clines[rline].count = hc->tcount / NCACHE_LINES + 1;
    hc->tcount += hc->clines[rline].count;

    memcpy(buf, hc->clines[rline].buf, LINE_SIZE);

    DEBUG_PRINT("Cache miss block %d, used cache line %d\n", blockno, rline);

    #ifdef DEBUG
	print_cline_counts(hc);
    #endif


    return 0;
}

int close_file(HCACHE hc){
    close(hc->fd);
    DEBUG_PRINT("Cache closed!\n");
    free(hc);
}

static size_t select_line(HCACHE hc){

    size_t min_count;
    size_t min_index;
    int i;

    min_count = hc->clines[0].count;
    min_index = 0;

    for (i = 1; i < NCACHE_LINES; ++i)
        if (hc->clines[i].count < min_count){
            min_count = hc->clines[i].count;
            min_index = i;
        }
    

    return min_index;
}

#ifdef DEBUG
static void print_cline_counts(HCACHE hc){
    int i;
    putchar('\n');
    printf("Total count: %llu\n", (unsigned long long)hc->tcount);
    for (i = 0; i < NCACHE_LINES; ++i)
        printf("Cache Line %d --> Block: %d, Count: %lu\n", i, hc->clines[i].blockno, (unsigned long)hc->clines[i].count);
    putchar('\n');
}

#endif
