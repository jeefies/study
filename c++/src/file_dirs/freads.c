#include <stdlib.h>
#include <stdio.h>

void main() {
	FILE * fp = fopen("freads.c", "rb");
	fseek(fp, 4, SEEK_SET);
	printf("4th is %c\n", fgetc(fp));
}
