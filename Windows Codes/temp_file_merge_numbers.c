#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TOTAL_SIZE         10000
#define PARTIAL_COUNT      10
#define PARTIAL_SIZE       (TOTAL_SIZE / PARTIAL_COUNT)
#define RANDOM_FILE_PATH   "random.dat"
#define RESULT_FILE_PATH   "result.dat"

struct merge_info {
    FILE* f;
    int curval;
};

FILE* create_random_file(void);
void bsort(int* pi, size_t size);
int getmin_index(const struct merge_info* mi, int size);
int verify_result(FILE* f, int size);

int main(void) {
    FILE* fr, * fd;
    struct merge_info mi[PARTIAL_COUNT];
    int i, size, min_index;
    int* buf;



    if ((fr = create_random_file()) == NULL) {
        fprintf(stderr, "cannot create random file!..\n");
        exit(EXIT_FAILURE);
    }

    if ((fd = fopen(RESULT_FILE_PATH, "w+b")) == NULL) {
        fprintf(stderr, "cannot create destination file!..\n");
        exit(EXIT_FAILURE);
    }

    if ((buf = (int*)malloc(PARTIAL_SIZE * sizeof(int))) == NULL) {
        fprintf(stderr, "cannot allocate memory!..\n");
        exit(EXIT_FAILURE);
    }

    rewind(fr); //File pointer rewinded
    for (i = 0; i < PARTIAL_COUNT; ++i)
    {
        if (fread(buf, sizeof(int), PARTIAL_SIZE, fr) != PARTIAL_SIZE) {
            fprintf(stderr, "cannot read random file!..\n");
            exit(EXIT_FAILURE);
        }
        bsort(buf, PARTIAL_SIZE);
        if ((mi[i].f = tmpfile()) == NULL) {
            fprintf(stderr, "cannot create temporary file!..\n");
            free(buf);
            exit(EXIT_FAILURE);
        }
        if (fwrite(buf, sizeof(int), PARTIAL_SIZE, mi[i].f) != PARTIAL_SIZE) {
            fprintf(stderr, "cannot write random file!..\n");
            exit(EXIT_FAILURE);
        }
        rewind(mi[i].f);
    }
    fclose(fr);

    for (i = 0; i < PARTIAL_COUNT; ++i)/*First element of the each file is assigned to curval variable*/
        if (fread(&mi[i].curval, sizeof(int), 1, mi[i].f) != 1) {
            fprintf(stderr, "cannot read temporary file!..\n");
            exit(EXIT_FAILURE);
        }
    size = PARTIAL_COUNT;

    while (size > 0) {
        min_index = getmin_index(mi, size);
        if (fwrite(&mi[min_index].curval, sizeof(int), 1, fd) != 1) {
            fprintf(stderr, "cannot write destination file!..\n");
            exit(EXIT_FAILURE);
        }
        /*File pointer already moved forward*/
        if (fread(&mi[min_index].curval, sizeof(int), 1, mi[min_index].f) != 1) {
            if (ferror(mi[min_index].f)) {//Check if there is an IO error
                fprintf(stderr, "cannot read temporary file!..\n");
                exit(EXIT_FAILURE);
            }
            /*If there is nothing else to read it doesn't look for the second time*/
            mi[min_index] = mi[size - 1];
            --size;
        }
    }
    rewind(fd);
    printf("%s\n", verify_result(fd, TOTAL_SIZE) ? "Verify Ok...\n" : "Verify failed...\n");

    free(buf);
    fclose(fd);

    return 0;
}
FILE* create_random_file(void) {
    FILE* f;
    int i, val;

    srand((unsigned)time(NULL));

    if ((f = fopen(RANDOM_FILE_PATH, "w+b")) == NULL) //Open in w+b mode read afterwards
        return NULL;

    for (i = 0; i < TOTAL_SIZE; ++i)
    {
        val = rand();
        if (fwrite(&val, sizeof(int), 1, f) != 1)
            return NULL;
    }

    return f;
}
void bsort(int* pi, size_t size) {
    size_t i, k;
    int temp;

    for (i = 0; i < size - 1; ++i)
        for (k = 0; k < size - 1 - i; ++k)
            if (pi[k] > pi[k + 1]) {
                temp = pi[k];
                pi[k] = pi[k + 1];
                pi[k + 1] = temp;
            }
}
int getmin_index(const struct merge_info* mi, int size) {
    int i, min_index = 0;

    for (i = 1; i < size; ++i)
        if (mi[i].curval < mi[min_index].curval)
            min_index = i;

    return min_index;
}
int verify_result(FILE* f, int size) {
    int val, prev_val;
    int i;

    if (fread(&prev_val, sizeof(int), 1, f) != 1)
        return 0;

    for (i = 1; i < size; ++i) {
        if (fread(&val, sizeof(int), 1, f) != 1)
            return 0;
        if (val < prev_val)
            return 0;
        prev_val = val;
    }
    return ftell(f) == size * sizeof(int); //File pointer offset must be equal to size
}
