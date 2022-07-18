#include <stdio.h>
#include <stdlib.h>

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

	qsort(persons, 5, sizeof(struct PERSON), cmp);
	for (i = 0; i < 5; ++i)
		printf("%-20s%d\n", persons[i].name, persons[i].no);

	return 0;
}
