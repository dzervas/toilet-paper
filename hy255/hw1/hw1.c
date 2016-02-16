/*
Dimitris Zervas <dzervas@dzervas.gr> [A.M. 3502]
Date 16/02/2016

Licensed under the beer-ware license.
"THE BEER-WARE LICENSE" (Revision 42):
dzervas <dzervas@dzervas.gr> wrote this code (unless said otherwise in the file).
As long as you retain this notice and I am mensioned somewhere in the credits (if any),
you can do whatever you want with this stuff. If we meet some day, and you think this stuff is worth it,
you can buy me a beer in return.
*/
#include <stdio.h>
#include <stdlib.h>

unsigned char table[][3] = {
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
	{ 243, 't', 0 },
	{ 244, 'y', 0 },
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
	{ 217, 'W', 0 },

	{ 220, 'a', '\'' },
	{ 221, 'e', '\'' },
	{ 222, 'h', '\'' },
	{ 223, 'i', '\'' },
	{ 252, 'o', '\'' },
	{ 253, 'w', '\'' },
	{ 254, 'y', '\'' },

	{ 182, 'A', '\'' },
	{ 184, 'E', '\'' },
	{ 185, 'H', '\'' },
	{ 186, 'I', '\'' },
	{ 188, 'O', '\'' },
	{ 191, 'W', '\'' },
	{ 190, 'Y', '\'' },

	{ 250, 'i', '\"' },
	{ 251, 'y', '\"' },
	{ 192, 'i', '\"' }, /* dialitika & tono */
	{ 224, 'y', '\"' }, /* dialitika & tono */

	{ 218, 'I', '\"' },
	{ 219, 'Y', '\"' },
	{ 0, 0, 0 }
};

int main() {
	unsigned char c, i;

	for (c = getchar(); c != EOF; c = getchar()) {
		if ((c >= 193 && c <= 217) || (c >= 225 && c <= 249) ||
			(c >= 220 && c <= 223) || (c >= 252 && c <= 254) || /* Accented letter */
			c == 182 || c == 187 || (c >= 184 && c <= 186) ||
			(c >= 190 && c <= 191) || c == 250 || c == 251 ||
			c == 192 || c == 224 || c == 218 || c == 219) {
			for (i = 0; table[i][0] != 0; i++) {
				if (table[i][0] == c) {
					printf("%c", table[i][1]);

					if (table[i][2])
						printf("%c", table[i][2]);
					if (c == 192 || c == 224)
						printf("\'");

					break;
				}
			}
		} else {
			printf("%c", c);
			continue;
		}
	}

	return 0;
}
