#include <stdio.h>

typedef void STATE(int);

/*STATE echo, techo, echot, echod, echotd, techod, second;

int nextstate(int);
int transcode(int);*/

int main() {
	int c, db = 0;
	unsigned char gr = 0;

	/*
	STATE *states[7] = {
		echo,
		echot,
		techo,
		echod,
		echotd,
		techod,
		second
 	};
 	*/

	for (c = getchar(); c != EOF; c = getchar()) {
		if (gr) {
			/* Small greek (a-o) && (p-w)*/
			if ((gr == 206 && c >= 177 && c <= 191) ||
					(gr == 207 && c >= 128 && c <= 137)) {
				printf("Small greek letter!\n");

				if (c == 188 || c == 189)
					db = c;
			} else if (gr == 206 && c >= 145 && c <= 169) {
				printf("Capital greek letter!\n");

				if (c == 188 || c == 189)
					db = c;
			} else if ((gr == 206 && c >= 172 && c <= 175) ||
					(gr == 207 && c >= 140 && c <= 142))
				printf("Small greek letter with accent\n");
			else if (gr == 206 && c >= 134 && c <= 143)
				printf("Capital greek letter with accent\n");
			else if (gr == 207 && c >= 138 && c <= 139)
				printf("Small greek letter with dialitika\n");
			else if (gr == 206 && c >= 170 && c <= 171)
				printf("Capital greek letter with dialitika\n");
			else if (gr == 206 && (c == 144 || c == 176))
				printf("Small greek letter with accent & dialitika\n");
			else if (gr == 194)
				printf("Greek punctuation");
			gr = 0;
		} else if (c == 206 || c == 207 || c == 194) {
			gr = c;
			printf("GR %d: ", c);
		} else if (!gr && c != '\n'){
			printf("Reg %c\n", (char) c);
		}
	}

	return 0;
}

/*
int nextstate(int c) {
	if (c )
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
*/

int transcode(int c) {
	int table[][3] = {
		{ 177, 'a', 0 },
		{ 177, 'a', 0 },
		{ 178, 'v', 0 },
		{ 179, 'g', 0 },
		{ 180, 'd', 0 },
		{ 181, 'e', 0 },
		{ 181, 'e', 0 },
		{ 182, 'z', 0 },
		{ 183, 'h', 0 },
		{ 183, 'h', 0 },
		{ 184, '8', 0 },
		{ 185, 'i', 0 },
		{ 185, 'i', 0 },
		{ 185, 'i', 0 },
		{ 185, 'i', 0 },
		{ 186, 'k', 0 },
		{ 187, 'l', 0 },
		{ 188, 'm', 0 },
		{ 189, 'n', 0 },
		{ 190, 'k', 's' },
		{ 191, 'o', 0 },
		{ 191, 'o', 0 },

		{ 128, 'p', 0 },
		{ 129, 'r', 0 },
		{ 130, 's', 0 },
		{ 131, 's', 0 },
		{ 132, 't', 0 },
		{ 133, 'y', 0 },
		{ 133, 'y', 0 },
		{ 133, 'y', 0 },
		{ 133, 'y', 0 },
		{ 134, 'f', 0 },
		{ 135, 'x', 0 },
		{ 136, 'p', 's' },
		{ 137, 'w', 0 },
		{ 137, 'w', 0 },

		{ 145, 'A', 0 },
		{ 145, 'A', 0 },
		{ 146, 'V', 0 },
		{ 147, 'G', 0 },
		{ 148, 'D', 0 },
		{ 149, 'E', 0 },
		{ 149, 'E', 0 },
		{ 150, 'Z', 0 },
		{ 151, 'H', 0 },
		{ 151, 'H', 0 },
		{ 152, '8', 0 },
		{ 153, 'I', 0 },
		{ 153, 'I', 0 },
		{ 153, 'I', 0 },
		{ 153, 'I', 0 },
		{ 154, 'K', 0 },
		{ 155, 'L', 0 },
		{ 156, 'M', 0 },
		{ 157, 'N', 0 },
		{ 158, 'K', 'S' },
		{ 159, 'O', 0 },
		{ 159, 'O', 0 },
		{ 160, 'P', 0 },
		{ 161, 'R', 0 },
		{ 163, 'S', 0 },
		{ 164, 'T', 0 },
		{ 165, 'Y', 0 },
		{ 165, 'Y', 0 },
		{ 165, 'Y', 0 },
		{ 165, 'Y', 0 },
		{ 166, 'F', 0 },
		{ 167, 'X', 0 },
		{ 168, 'P', 'S' },
		{ 169, 'W', 0 },
		{ 169, 'W', 0 },
	};

	return 0;
}
