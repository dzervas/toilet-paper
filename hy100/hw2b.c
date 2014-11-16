/*
 * Coded by Dimitris Zervas <dzervas@dzervas.gr> [A.M. 3502]
 * Knife game calculator
 */
#include <stdio.h>

int main() {
	unsigned int number;
	
	printf("Give the number of the players (up to 2^%d): ", (int)(sizeof(unsigned int) * 8));
	scanf(" %ud", &number);

	/*
	 * If number = 2^m + l, then result 2l + 1
	 * So, I try to find l. I start with the bigger number the pc supports (probably 2^32)
	 * and bitwise and it with number. If the result is not 0, I found the most significant
	 * bit of the number, if not, continue.
	 * l is the bits left in the number AFTER the most significant bit, so I AND the NOT
	 * of test with the number to zero out the MSB.
	 */
	for (unsigned int test = (1 << (int)(8 * sizeof(unsigned int) - 2)); test > 0; test >>= 1) {
		if ((number & test) != 0) {
			printf("The last player left is %d\n", 2 * (number & ~test) + 1);
			break;
		}
	}

	return 0;
}
