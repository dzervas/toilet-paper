#include "stdio.h"
#include "stdlib.h"

int maxnum;
char *table;

void show();
void towers(int, char, char, char);

int main() {
	int i;

	printf("Enter the number of disks : ");
	if (!scanf("%d", &maxnum))
		printf("Error!");

	table = (char *) malloc(maxnum * sizeof(unsigned short int));
	towers(maxnum, 'A', 'C', 'B');
	free(table);

	return 0;
}

void towers(int num, char from, char to, char other) {
	if(num == 1) {
		table[0] = to;
		show();
		printf("%c -> %c\n", from, to);
		return;
	}

	/* Move top i-1 disks from A to B,  using C as auxiliary */
	towers(num - 1, from, other, to);
	/* Move remaining disks from A to C */

	table[num - 1] = to;
	show();
	printf("%c -> %c\n", from, to);
	/* Move n-1 disks from B to C using A as auxiliary */
	towers(num - 1, other, to, from);
}

void show() {
	int i, j;

	for (i = 0; i < (((maxnum - 1) * 2 + 1) * 3 + 2); i++) {
		if ((i % ((maxnum - 1) * 2 + 1)) / 2 == maxnum - 1)
			printf("%c", 'A' + ((maxnum - 1) * 2 + 1));
		else
			printf(" ");
	}

	printf("\n\n");

	for (i = 0; i < (((maxnum - 1) * 2 + 1) * 3 + 2); i++) {
		if ((i % ((maxnum - 1) * 2 + 1)) / 2 == maxnum - 1)
			printf("|");
		else
			printf(" ");
	}

	printf("\n");

	for (j = 0; j < maxnum; j++) {
		for (i = 0; i < (((maxnum - 1) * 2 + 1) * 3 + 2); i++) {
			if ((i % ((maxnum - 1) * 2 + 1)) / 2 == maxnum - 1)
				printf("%d", j + 1);
			else
				printf(" ");
		}
		printf("\n");
	}
}
