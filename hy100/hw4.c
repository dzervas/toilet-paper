#include "stdio.h"

int maxnum;
unsigned short int *table;

void show(int, char, char, char);
void towers(int, char, char, char);

int main() {
	int i;

	printf("Enter the number of disks : ");
	if (!scanf("%d", &maxnum))
		printf("Error!");

	table = malloc(maxnum * sizeof(unsigned short int));

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

	towers(maxnum, 'A', 'C', 'B');
	free(table);

	return 0;
}

void towers(int num, char from, char to, char other) {
	if(num == 1) {
		printf("Move disk 1 %c -> %c\n", from, to);
		return;
	}

	/* Move top i-1 disks from A to B,  using C as auxiliary */
	towers(num - 1, from, other, to);
	/* Move remaining disks from A to C */
	printf("Move disk %d %c -> %c\n", num, from, to);
	/* Move n-1 disks from B to C using A as auxiliary */
	towers(num - 1, other, to, from);
}

void show(int num, char A, char B, char C) {
	int i, j, k, tmp;
	for (i = 0; i <= maxnum; i++) {
		tmp = (i * 2) + 1;
		for (j = 0; j < (maxnum * 3 + 2); j++) {
			if ((tmp / 2) < (maxnum / 2))
				printf("burp!\n");
		}
	}
}
