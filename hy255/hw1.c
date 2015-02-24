#include <stdio.h>

typedef void STATE(int);

STATE echo, techo, echot, echod, echotd, techod, second;

int nextstate(int);
int transcode(int);

int main() {
	int c;

	STATE *states[7] = {
		echo,
		echot,
		techo,
		echod,
		echotd,
		techod,
		second
	};

	c = getchar();
}

int nextstate(int c) {
	switch (c) {
		// Non capital with tono
		case 1 :
			return 1;
			break;
		// Capital with tono
		case 1 :
			return 2;
			break;
		// Dialitika
		case 1 :
			return 3;
			break;
		// Non capital with tono and dialitika
		case 1 :
			return 4;
			break;
		// Capital with tono and dialitika
		case 1 :
			return 5;
			break;
		// 2 letter letter
		case 1 :
			return 6;
			break;
		// Simple echo
		default:
			return 0;
			break;
	}
}

int transcode(int c) {
	int table[3][48] = {
		{ 225, 'a', 0 },
		{ 226, 'v', 0 },
		{ 227, 'g', 0 },
		{ 228, 'd', 0 },
		{ 229, 'e', 0 },
		{ 230, 'z', 0 },
		{ 231, 'h', 0 },
		{ 232, '8', 0 },
		{ 233, 'i', 0 },
		{ 234, 'k', 0 },
		{ 235, 'l', 0 },
		{ 236, 'm', 0 },
		{ 237, 'n', 0 },
		{ 238, 'k', 's' },
		{ 239, 'o', 0 },
		{ 240, 'p', 0 },
		{ 241, 'r', 0 },
		{ 242, 's', 0 },
		{ 243, 's', 0 },
		{ 244, 't', 0 },
		{ 245, 'y', 0 },
		{ 246, 'f', 0 },
		{ 247, 'x', 0 },
		{ 248, 'p', 's' },
		{ 249, 'w', 0 },

		{ 193, 'A', 0 },
		{ 194, 'V', 0 },
		{ 195, 'G', 0 },
		{ 196, 'D', 0 },
		{ 197, 'E', 0 },
		{ 198, 'Z', 0 },
		{ 199, 'H', 0 },
		{ 200, '8', 0 },
		{ 201, 'I', 0 },
		{ 202, 'K', 0 },
		{ 203, 'L', 0 },
		{ 204, 'M', 0 },
		{ 205, 'N', 0 },
		{ 206, 'K', 'S' },
		{ 207, 'O', 0 },
		{ 208, 'P', 0 },
		{ 209, 'R', 0 },
		{ 211, 'S', 0 },
		{ 212, 'T', 0 },
		{ 213, 'Y', 0 },
		{ 214, 'F', 0 },
		{ 215, 'X', 0 },
		{ 216, 'P', 'S' },
		{ 217, 'W', 0 }
	}
}
