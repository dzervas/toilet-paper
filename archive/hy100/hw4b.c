#include <stdio.h>
#include <stdlib.h>

unsigned char unique(int *array);

int main(int argc, char *argv[]) {
	int m, n, input[9][9], buffer[9], errors[3][9] = { { 0 }, { 0 }, { 0 } };
	unsigned char i, j, k, errkeep[3] = { 0 };

	printf("Give n m: ");
	if (scanf("%d %d", &n, &m) != 2)
		return 1;

	for (i = 0; i < m * n; i++) {
		for (j = 0; j < m * n; j++) {
			if (scanf("%d", &input[i][j]) != 1)
				return 1;
		}
	}

	for (i = 0; i < m*n; i++) {
		/* Line check */
		if (!unique(input[i]))
			errors[0][errkeep[0]++] = i + 1;

		/* Row check */
		for (j = 0; j < m*n; j++)
			buffer[j] = input[j][i];

		if (!unique(buffer))
			errors[1][errkeep[1]++] = i + 1;

		/* Block check */
		if ((i % m) == 0) {
			for (j = 0; j < m*n; j++) {
				for (k = 0; k < n; k++)
					buffer[(j % n) * n + k] = input[(i / 3) *3 + k][j];

				if ((j % m) == 2) {
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
