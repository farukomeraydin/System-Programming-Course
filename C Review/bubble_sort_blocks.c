#include <stdio.h>

void bsort(void* pv, size_t count, size_t width, int (*compare)(const void*, const void*)) {
	size_t i, k, j;
	char* pc = (char*)pv; //This conversion is not necessary in C but we did it anyway.
	char* pc1, * pc2;
	char temp;

	for (i = 0; i < count - 1; ++i)
		for (k = 0; k < count - 1 - i; ++k) {
			pc1 = pc + k * width;
			pc2 = pc + (k + 1) * width;
			if (compare(pc1, pc2) > 0)
				for (j = 0; j < width; ++j) { //Swapped every element in a block
					temp = pc1[j];
					pc1[j] = pc2[j];
					pc2[j] = temp;
				}
		}
}

struct PERSON {
	char name[32];
	int no;
};

int cmp(const void* pv1, const void* pv2) {
	const struct PERSON* per1 = (const struct PERSON*)pv1;
	const struct PERSON* per2 = (const struct PERSON*)pv2;

	if (per1->no > per2->no)
		return 1;
	if (per1->no < per2->no)
		return -1;
	return 0;
}

int main(void) {
	struct PERSON persons[] = {
		{"Ali Serce", 123},
		{"Veli Boz", 782},
		{"Sacit Apaydin", 824},
		{"Macit Flordun", 623},
		{"Tansu Ciller", 482}
	};
	int i;

	bsort(persons, 5, sizeof(struct PERSON), cmp);
	for (i = 0; i < 5; ++i)
		printf("%-20s%d\n", persons[i].name, persons[i].no);

	return 0;
}
