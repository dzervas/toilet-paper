#include <stdio.h>
/* Instead of a regular array, I use 2 ints as 2 boolean arrays that hold each player's moves */
unsigned int playerX = 0, playerO = 0;

unsigned char check();
unsigned int input();
unsigned char masker(unsigned int mask, unsigned int *player);
char show(unsigned char i);

int main(int argc, char *argv[]) {
	unsigned char i, count = 0;

	while (1) {
		/* Check for (very) wild error */
		if ((playerX & playerO) != 0) {
			printf("WOW. That's very weird... X: %u O: %u", playerX, playerO);
			return 1;
		}

		for (i = 0; i < 5; i++) {
			if (i % 2)
				printf("---+---+---\n");
			else
				/* This condition is hit for i=0, 2, 4 and I need 0,1,2 for i=0,
				3, 4, 5 for i=1 and 6,7,8 for i=2, so I use (i + (i/2)) to get
				the "base" I need for each line (0 for first line, 3 for second
				and 6 for third line). Then I add the number of column. */
				printf(" %c | %c | %c\n",
						show(i + (i/2)),
						show(i + (i/2) + 1),
						show(i + (i/2) + 2));
		}

		/* 0 is player X, 1 is player O*/
		if (count == 2)
			break;
		else if (count) {
			printf("Player O: ");
			playerO |= input();
		} else {
			printf("Player X: ");
			playerX |= input();
		}

		/* Cycle "count" between 0 and 1 by xoring it with 1 */
		count ^= 1;

		if (!check())
			count = 2;
	}

	return 0;
}

unsigned char check() {
	unsigned int *player = &playerX;
	unsigned char i, j;

	for (i = 0; i < 2; i++) {
		if (i)
			player = &playerO;

		/* I use win "masks" that let me automate the process of checking rows or
		columns won, by shifting them accoridngly. I bitwise AND the shifted mask
		with each player's array to check if he has won.*/
		/* Check for 000000111 = 7 win mask, row mask */
		for (j = 0; j < 3; j++) {
			if (masker((7 << 3*j), player))
				return 0;
		}

		/* Check for 001001001 = 73 win mask, column mask */
		for (j = 0; j < 3; j++) {
			if (masker((73 << j), player))
				return 0;
		}

		/* Diagonal wins  are just 1 condition, so there is no reason shifting them */
		/* Check for 0b100010001 = 273 win mask, left diagonal mask */
		if (masker(273, player))
			return 0;

		/* Check for 0b001010100= 84 win mask, right diagonal mask */
		printf("%d\n", *player);
		if (masker(84, player)) {
			return 0;
		}
	}

	/* If the matrix is filled and none has won, it's a tie */
	/* 111111111 = 511*/
	if ((playerX | playerO) == 511) {
		printf("It's a tie!\n");
		return 0;
	}

	return 1;
}

unsigned int input() {
	unsigned int buffer, mixed = playerX | playerO;

	if (scanf(" %u", &buffer) != 1) {
		printf("Error, input must be number: ");
		return input();
	}

	if (buffer < 1 || buffer > 9) {
		printf("Error, number must be 1-9: ");
		return input();
	}

	--buffer;

	/* Mixed has the taken places of the matrix (regardless of player).
	I check if the player tries to overwrite one of them.*/
	if ((mixed & (1 << buffer)) >> buffer) {
		printf("Error, place is already taken: ");
		return input();
	}

	return (1 << buffer);
}

unsigned char masker(unsigned int mask, unsigned int *var) {
	if ((mask & *var) == mask) {
		printf("Player %c wins!\n", (var == &playerX) ? 'X' : 'O');
		return 1;
	}

	return 0;
}

/* Shows the appropriate character (X or O) for the place of the tic tac toe matrix */
char show(unsigned char index) {
	/* (playerX & (1 << index)) Get the bit of index (0 or 1)
	 >> index and shift it to make this a boolean conditioni */
	if ((playerX & (1 << index)) >> index)
		return 'X';
	else if ((playerO & (1 << index)) >> index)
		return 'O';
	return ' ';
}
