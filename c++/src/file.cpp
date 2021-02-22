#include <stdio.h>

int getLength(char matrix[]);

int main() {
	char x[256];
	FILE *fptr;

	fptr = fopen("s.cpp", "r");
	unsigned int block = fread(x, 128, 2, fptr);
	printf("%u\n", block);

	printf(x);
	printf("\n");
	printf("%d", getLength(x));

	return 0;
}
