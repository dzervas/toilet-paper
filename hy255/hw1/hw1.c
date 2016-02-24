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

#define MAP(ch) (table[ch - 182][0])

int table[][3] = {
	/* 182 */ { '\'', 'A' },

	/* 183 */ { '.', 0 },
	
	/* 184 */ { '\'', 'E' },
	/* 185 */ { '\'', 'H' },
	/* 186 */ { '\'', 'I' },
	
	/* 187 */ { 187, 0 },
	
	/* 188 */ { '\'', 'O' },
	
	/* 189 */ { 189, 0 },
	
	/* 190 */ { '\'', 'Y' },
	/* 191 */ { '\'', 'W' },
	
	/* 192 */ { 'i', '\'' }, /* dialitika & tono */

	/* 193 */ { 'A', 0 },
	/* 194 */ { 'V', 0 },
	/* 195 */ { 'G', 0 },
	/* 196 */ { 'D', 0 },
	/* 197 */ { 'E', 0 },
	/* 198 */ { 'Z', 0 },
	/* 199 */ { 'H', 0 },
	/* 200 */ { '8', 0 },
	/* 201 */ { 'I', 0 },
	/* 202 */ { 'K', 0 },
	/* 203 */ { 'L', 0 },
	/* 204 */ { 'M', 0 },
	/* 205 */ { 'N', 0 },
	/* 206 */ { 'K', 'S' },
	/* 207 */ { 'O', 0 },
	/* 208 */ { 'P', 0 },
	/* 209 */ { 'R', 0 },
	
	/* 210 */ { 210, 0 },
	
	/* 211 */ { 'S', 0 },
	/* 212 */ { 'T', 0 },
	/* 213 */ { 'Y', 0 },
	/* 214 */ { 'F', 0 },
	/* 215 */ { 'X', 0 },
	/* 216 */ { 'P', 'S' },
	/* 217 */ { 'W', 0 },
	
	/* 218 */ { 'I', '\"' },
	/* 219 */ { 'Y', '\"' },
	
	/* 220 */ { 'a', '\'' },
	/* 221 */ { 'e', '\'' },
	/* 222 */ { 'h', '\'' },
	/* 223 */ { 'i', '\'' },
	/* 224 */ { 'y', '\'' }, /* dialitika & tono */

	/* 225 */ { 'a', 0 },
	/* 226 */ { 'v', 0 },
	/* 227 */ { 'g', 0 },
	/* 228 */ { 'd', 0 },
	/* 229 */ { 'e', 0 },
	/* 230 */ { 'z', 0 },
	/* 231 */ { 'h', 0 },
	/* 232 */ { '8', 0 },
	/* 233 */ { 'i', 0 },
	/* 234 */ { 'k', 0 },
	/* 235 */ { 'l', 0 },
	/* 236 */ { 'm', 0 },
	/* 237 */ { 'n', 0 },
	/* 238 */ { 'k', 's' },
	/* 239 */ { 'o', 0 },
	/* 240 */ { 'p', 0 },
	/* 241 */ { 'r', 0 },
	/* 242 */ { 's', 0 },
	/* 243 */ { 's', 0 },
	/* 244 */ { 't', 0 },
	/* 245 */ { 'y', 0 },
	/* 246 */ { 'f', 0 },
	/* 247 */ { 'x', 0 },
	/* 248 */ { 'p', 's' },
	/* 249 */ { 'w', 0 },
	
	/* 250 */ { 'i', '\"' },
	/* 251 */ { 'y', '\"' },
	
	/* 252 */ { 'o', '\'' },
	/* 253 */ { 'y', '\'' },
	/* 254 */ { 'w', '\'' },
};

int main() {
	int c, buff;
	/* Zero value is 182  to avoid checking if buff >= 182*/
	buff = 182;

	for (c = getchar(); c != EOF; c = getchar()) {
		if (c >= 182 && c < 255) {
			if (MAP(buff) == 'm' && (MAP(c) == 'p' || MAP(c) == 'P'))
				c = 'b';
			else if (MAP(buff) == 'M' && (MAP(c) == 'p' || MAP(c) == 'P'))
				c = 'B';
			else if (MAP(buff) == 'n' && (MAP(c) == 't' || MAP(c) == 'T'))
				c = 'd';
			else if (MAP(buff) == 'N' && (MAP(c) == 't' || MAP(c) == 'T'))
				c = 'D';
			else if (buff != 182)
				printf("%c", MAP(buff));
		}

		if (c >= 182 && c < 255) {
			switch (MAP(c)) {
				case 'm':
				case 'M':
				case 'n':
				case 'N':
					buff = c;
					break;
				default:
					buff = 182;
					break;
			}

			if (buff == c && buff != 182)
				continue;

			printf("%c", MAP(c));

			if (table[c - 182][1])
				printf("%c", table[c - 182][1]);
			if (c == 192 || c == 224)
				printf("\"");
		} else {
			printf("%c", c);
			buff = 182;
		}
	}

	return 0;
}
