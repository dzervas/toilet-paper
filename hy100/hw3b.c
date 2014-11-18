#include <stdio.h>

unsigned char unique(int *array);

int main(int argc, char *argv[]) {
	int input[9][9], buffer[9], errors[3][9] = { { 0 }, { 0 }, { 0 } };
	unsigned char i, j, k, errkeep[3] = { 0 };

	for (i = 0; i < 9; i++) {
		if (scanf("%d %d %d %d %d %d %d %d %d", &input[i][0], &input[i][1], &input[i][2],
					&input[i][3], &input[i][4], &input[i][5], &input[i][6],
					&input[i][7], &input[i][8]) != 9)
			return 1;
	}

	for (i = 0; i < 9; i++) {
		/* Line check */
		if (!unique(input[i]))
			errors[0][errkeep[0]++] = i + 1;


		/* Row check */
		for (j = 0; j < 9; j++)
			buffer[j] = input[j][i];

		if (!unique(buffer))
			errors[1][errkeep[1]++] = i + 1;

		/* Block check */
		if ((i % 3) == 0) {
			for (j = 0; j < 9; j++) {
				for (k = 0; k < 3; k++)
					buffer[(j % 3) * 3 + k] = input[(i / 3) *3 + k][j];

				if ((j % 3) == 2) {
					if (!unique(buffer))
						errors[2][errkeep[2]++] = 1 + i + j / 3;
				}
			}
		}
	}

	printf("Line errors: ");
	for (i = 0; i < errkeep[0]; i++)
		printf("%d ", errors[0][i]);

	printf("\nRow errors: ");
	for (i = 0; i < errkeep[1]; i++)
		printf("%d ", errors[1][i]);

	printf("\nBlock errors: ");
	for (i = 0; i < errkeep[2]; i++)
		printf("%d ", errors[2][i]);

	printf("\n");
	return 0;
}

unsigned char unique(int *array) {
	unsigned char buff[9], i;

	for (i = 0; i < 9; i++)
		buff[i] = 0;

	for (i = 0; i < 9; i++) {
		if (buff[array[i] - 1] != 0)
			return 0;

		buff[array[i] - 1]++;
	}

	return 1;
}
