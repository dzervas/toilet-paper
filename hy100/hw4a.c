#include "stdio.h"
#include "stdlib.h"

int maxnum, *cols[3], numcols[3] = { 0 };

void show();
void towers(int, char, char, char);

int main() {
	int i;

	printf("Enter the number of disks : ");
	if (!scanf("%d", &maxnum))
		printf("Error!");

	for (i = 0; i < 3; i++)
		cols[i] = (int*) malloc(maxnum * sizeof(int));
	
	numcols[0] = maxnum;
	for (i = 0; i < maxnum ; i++)
		cols[0][maxnum - i - 1] = i + 1;

	show();
	towers(maxnum, 'A', 'C', 'B');

	for (i = 0; i < 3; i++)
		free(cols[i]);

	return 0;
}

void towers(int num, char from, char to, char other) {
	if(num == 1) {
		numcols[from - 65]--;
		cols[from - 65][numcols[from - 65]] = 0;

		cols[to - 65][numcols[to - 65]] = num;
		numcols[to - 65]++;

		printf("%c -> %c\n", from, to);
		show();

		return;
	}

	towers(num - 1, from, other, to);

	numcols[from - 65]--;
	cols[from - 65][numcols[from - 65]] = 0;

	cols[to - 65][numcols[to - 65]] = num;
	numcols[to - 65]++;

	printf("%c -> %c\n", from, to);
	show();

	towers(num - 1, other, to, from);
}

void show() {
	int i, j;

	for (i = 0; i < (((maxnum - 1) * 2 + 1) * 3 + 2); i++) {
		if ((i % ((maxnum - 1) * 2 + 1)) / 2 == maxnum - 1)
			printf("%c", 'A' + (i / ((maxnum - 1) * 2 + 1)));
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

	for (j = maxnum - 1; j >= 0; j--) {
		for (i = 0; i < (((maxnum - 1) * 2 + 1) * 3 + 2); i++) {
			if (((i % ((maxnum - 1) * 2 + 1)) / 2 == maxnum - 1)) {
				if (cols[i / ((maxnum - 1) * 2 + 1)][j] != 0)
					printf("%d", cols[i / ((maxnum - 1) * 2 + 1)][j]);
				else
					printf("|");
			} else
				printf(" ");
		}
		printf("\n");
	}

	printf("\n");
}
