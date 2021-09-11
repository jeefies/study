#include <stdio.h>

struct Point {
	int a;
	int b;
	char * str;
};
typedef struct Point Point;

int main(int argc, char* argv[]) {
	Point pt = {1, 2, "string here\n"};
	printf("%d, %d\n", pt.a, pt.b);
	printf("%s", pt.str);
	return 0;
}
