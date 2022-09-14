#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
	char helloWorld[] = "Hello World!"; // strlen(12), memory length 13 bytes
	char helloWorldChars[] = {'H', 'e', 'l', 'l', '!', '\0'};
	char * dst;
	dst = (char *)malloc(sizeof(char) * (strlen(helloWorld) + 1));
	if (dst == NULL)
		printf("Allocate memory failed!\n");
	else
		strcpy(dst, helloWorld);

	free(dst);
}
