//gcc sample.c filecache.c -o sample
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include "filecache.h"

int create_test_file(const char* path, int nblocks);

int main(int argc, char* argv[]){
	
	HCACHE hc;
	char buf[32 + 1];
	int blockno;

#ifdef CREATE
	if (create_test_file("test.dat", 100) == -1){
		perror("create_test_file");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
#endif

	if ((hc = open_file("test.dat", O_RDONLY)) == NULL){
		fprintf(stderr, "cannot open file!..\n");
		exit(EXIT_FAILURE);
	}

	for (;;){
		printf("Block No:");
		scanf("%d", &blockno);
		putchar('\n');
		if (blockno == -1)
			break;

		if (read_file(hc, blockno, buf) == -1){
			perror("read_file");
			exit(EXIT_FAILURE);
		}

		buf[32] = '\0';
		printf("Block content: %s\n\n", buf);
	}

	close_file(hc);

	return 0;
}

int create_test_file(const char* path, int nblocks){
	FILE* f;
	int i, k;
	char buf[LINE_SIZE];


	srand(time(NULL));

	if ((f = fopen(path, "wb")) == NULL)
		return -1;

	for (i = 0; i < nblocks; ++i){
		sprintf(buf, "%04d ", i); //First 4 bytes will be in the buffer
		for (k = 5; k < 32; ++k)
			buf[k] = rand() % 26 + 'A';

		if (fwrite(buf, LINE_SIZE, 1, f) != 1)
			return -1;
	}

	fclose(f);
}
