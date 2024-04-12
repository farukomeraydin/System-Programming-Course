#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#pragma pack(1) //byte alignment.

struct BITMAP_HEADER {
	char magic[2];
	uint32_t size;
	uint16_t reserved1;
	uint16_t reserved2;
	uint32_t dataloc;
};


int main(void) {
	FILE* f;
	struct BITMAP_HEADER bh;
	if ((f = fopen("test.bmp", "rb")) == NULL) {
		fprintf(stderr, "Cannot open file!..\n");
		exit(EXIT_FAILURE);
	}

	fread(&bh, sizeof(struct BITMAP_HEADER), 1, f);
	printf("Magic: %c%c\n", bh.magic[0], bh.magic[1]);
	printf("Size: %u\n", bh.size);
	printf("Bitmap Data Location: %u\n", bh.dataloc);

	return 0;
}
