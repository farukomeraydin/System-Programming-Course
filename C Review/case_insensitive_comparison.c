#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct PERSON {
	char name[32];
	int no;
};

int cmp_no(const void* pv1, const void* pv2) {
	const struct PERSON* per1 = (const struct PERSON*)pv1;
	const struct PERSON* per2 = (const struct PERSON*)pv2;

	if (per1->no > per2->no)
		return 1;
	if (per1->no < per2->no)
		return -1;
	return 0;
}

int istrcmp(const char* s1, const char* s2) {
	while (tolower(*s1) == tolower(*s2)) {
		if (*s1 == '\0')
			return 0;
		++s1;
		++s2;
	}
	return tolower(*s1) - tolower(*s2);
}

int cmp_name(const void* pv1, const void* pv2) {
	const struct PERSON* per1 = (const struct PERSON*)pv1;
	const struct PERSON* per2 = (const struct PERSON*)pv2;

	return istrcmp(per1->name, per2->name);
}

int main(void) {
	struct PERSON persons[] = {
		{"ali Serce", 123},
		{"Veli Boz", 782},
		{"Sacit Apaydin", 824},
		{"Macit Flordun", 623},
		{"Tansu Ciller", 482}
	};
	int i;

	qsort(persons, 5, sizeof(struct PERSON), cmp_no);
	for (i = 0; i < 5; ++i)
		printf("%-20s%d\n", persons[i].name, persons[i].no);

	printf("--------------------------------------------------\n");

	qsort(persons, 5, sizeof(struct PERSON), cmp_name);
	for (i = 0; i < 5; ++i)
		printf("%-20s%d\n", persons[i].name, persons[i].no);
	return 0;
}
