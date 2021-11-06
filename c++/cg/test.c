#include <stdio.h>
#include <stdlib.h>

int main() {
	int i = 0b10;
	int i2 = atoi("10");

	printf("%d %d\n", i2, i);

	int a, b, c;

	scanf("%d%d%d", &a, &b, &c);

	printf("a, b, c = %d, %d, %d\n", a, b, c);
}
