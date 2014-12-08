#include "stdio.h"
#include "stdlib.h"

/* Formula to find the range to show the numbers */
#define RANGE(x)		(2 * x - 1)
/* Formula to transform capital letters to integers*/
#define CAPINT(x)		(x - 65)

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
		numcols[CAPINT(from)]--;
		cols[CAPINT(from)][numcols[CAPINT(from)]] = 0;

		cols[CAPINT(to)][numcols[CAPINT(to)]] = num;
		numcols[CAPINT(to)]++;

		printf("%c -> %c\n\n", from, to);
		show();

		return;
	}

	towers(num - 1, from, other, to);

	numcols[CAPINT(from)]--;
	cols[CAPINT(from)][numcols[CAPINT(from)]] = 0;

	cols[CAPINT(to)][numcols[CAPINT(to)]] = num;
	numcols[CAPINT(to)]++;

	printf("%c -> %c\n\n", from, to);
	show();

	towers(num - 1, other, to, from);
}

void show() {
	int i, j, k;

	for (i = 0; i < (RANGE(maxnum) * 3); i++) {
		if (i % RANGE(maxnum) == RANGE(maxnum) / 2)
			printf("%c", 'A' + (i / RANGE(maxnum)));
		else
			printf(" ");
	}

	printf("\n\n");

	for (i = 0; i < (RANGE(maxnum) * 3); i++) {
		if (i % RANGE(maxnum) == RANGE(maxnum) / 2)
			printf("|");
		else
			printf(" ");
	}

	printf("\n");

	for (j = maxnum - 1; j >= 0; j--) {
		for (k = 0; k < 3; k++) {
			for (i = 0; i < RANGE(maxnum); i++) {
				if (i < RANGE(cols[k][j]) + (RANGE(maxnum) - RANGE(cols[k][j])) / 2 && i >= (RANGE(maxnum) - RANGE(cols[k][j])) / 2) {
					if (cols[k][j] != 0)
						printf("%d", cols[k][j]);
					else
						printf("|");
				} else
					printf(" ");
			}
		}
		printf("\n");
	}

	for (i = 0; i < (RANGE(maxnum) * 3); i++)
		printf("-");

	printf("\n\n");
}
