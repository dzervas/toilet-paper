#include <stdio.h>

unsigned char unique(int *array);

int main(int argc, char *argv[]) {
	int input[9][9], buffer[9], errors[3][9] = { { 0 }, { 0 }, { 0 } };
	unsigned char i, j, k;

	for (i = 0; i < 9; i++) {
		if (scanf("%d %d %d %d %d %d %d %d %d", &input[i][0], &input[i][1], &input[i][2],
					&input[i][3], &input[i][4], &input[i][5], &input[i][6],
					&input[i][7], &input[i][8]) != 9)
			return 1;
	}

	for (i = 0; i < 9; i++) {
		/* Line check */
		if (!unique(input[i]))
			printf("Error in line: %d\n", i + 1);
		else
			printf("Line %d\n", i + 1);

		/* Row check */
		for (j = 0; j < 9; j++)
			buffer[j] = input[i][j];

		if (!unique(buffer))
			printf("Error in row: %d\n", i + 1);
		else
			printf("Row %d\n", i + 1);

		/* Block check */
		if ((i % 3) == 0) {
			for (j = 0; j < 9; j++) {
				for (k = 0; k < 3; k++) {
					buffer[(j % 3) * 3 + k] = input[(i % 3) *3 + k][j];
					printf("%d = %d[%d]\n", (j % 3) * 3 + k, (i % 3) * 3 + k, j);
				}

				if ((j % 3) == 2) {
					if (!unique(buffer))
						printf("Error in block: %d\n", 1 + i + j / 3);
					else
						printf("Block %d\n", 1 + i + j / 3);
				}
			}
		}
	}

	return 0;
}

unsigned char unique(int *array) {
	unsigned char buff[9], i;

	for (i = 0; i < 9; i++)
		buff[i] = 0;

	for (i = 0; i < 9; i++) {
		/*printf("%d\n", array[i] -1);*/
		if (array[i] == 0)
			printf("!!!");
		if (buff[array[i] - 1] != 0)
			return 0;

		buff[array[i] - 1]++;
	}

	return 1;
}
