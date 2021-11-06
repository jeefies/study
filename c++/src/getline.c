#include <stdio.h>
#include <stdlib.h>

struct String {
	int length;
	char * text;
};
typedef struct String String;

String mgetline(const char * pre) {
	if (pre != NULL) printf(pre);
	char * line = (char *)malloc(sizeof(char) * 5);
	char buf;
	int p = 0, count = 5;
	while (1) {
		scanf("%c", &buf);
		if (buf == '\n') break;
		line[p] = buf;
		p += 1;
		if (p == count) {
			count += 5;
			line = (char *)realloc(line, sizeof(char) * count);
		}
	}

	String str = {p, line};
	return str;

}

int main() {
	String line = mgetline("please enter your name:");
	return printf("Hello %s!\n", line.text);
}
