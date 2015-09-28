/*
 * Coded by Dimitris Zervas <dzervas@dzervas.gr> [A.M. 3502]
 * Simple fraction additon calculator.
 */
#include <stdio.h>

int main() {
	int aar, apar, bar, bpar;

	printf("Give 4 spaced, non-zero integers (a/b c/d), up to 2^%ld: ", (sizeof(int) * 8) - 1); 
	if (scanf("%d %d %d %d", &aar, &apar, &bar, &bpar) != 4) {
		printf("Error!");
		return 1;
	}

	printf("Result = %d / %d\n", aar * bpar + apar * bar, apar * bpar);

	return 0;
}
