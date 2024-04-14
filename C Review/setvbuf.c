/*
setvbuf changes buffer address and buffer size. Although in line buffered mode buffer only contains characters in a line, 
various libraries might fill the entire buffer during reading. However, during writing when '\n' is put buffer will be refreshed
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void disp_hex(const void* buf, size_t size, size_t lbytes)
{
	size_t i, k, remainder;
	unsigned char* cbuf = (unsigned char*)buf;

	for (i = 0; i < size; ++i) {
		if (i % lbytes == 0)
			printf("%08x ", (unsigned int)i);

		printf("%02X ", cbuf[i]);

		if (i % lbytes == lbytes - 1) {
			for (k = 0; k < lbytes; ++k)
				printf("%c", iscntrl(cbuf[i - lbytes + k]) ? '.' : cbuf[i - lbytes + k]);
			putchar('\n');
		}
	}

	remainder = size % lbytes;
	for (k = 0; k < 3 * (lbytes - remainder); ++k)
		putchar(' ');

	for (k = 0; k < remainder; ++k)
		printf("%c", iscntrl(cbuf[i - remainder + k]) ? '.' : cbuf[i - remainder + k]);
	putchar('\n');
}

int main(void)
{
	FILE* f;
	char buf[64] = { '\0' };

	if ((f = fopen("test.txt", "r+b")) == NULL) {
		fprintf(stderr, "cannot open file!..\n");
		exit(EXIT_FAILURE);
	}

	setvbuf(f, buf, _IOLBF, 64); //Only a 1 line will be buffered. When it comes to '\n' it will be flushed.
	fgetc(f);

	disp_hex(buf, 64, 16);

	fclose(f);

	return 0;
}
