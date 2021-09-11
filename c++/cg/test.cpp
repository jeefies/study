#include <iostream>
#include <cstring>

using namespace std;

struct kasjhdfliskhdfksd {
	int x;
} x;

int func(int x) {
	cout << x << endl;
	return x + 2;
}

char rc (kasjhdfliskhdfksd x) {
	return (char)x.x;
}

// (int *)(int x)
int (*func2)(int) = func;
auto func3 = func;

// (char *)(kasjhdfliskhdfksd)
char (*rc2)(kasjhdfliskhdfksd) = rc;
auto rc3 = rc;

int main() {
	x.x = 78;
	auto y = x;

	auto list = new int [10];

	cout << y.x << endl;

	cout << func2(5) <<  endl;
	cout << func3(5) <<  endl;

	cout << rc2(x) << endl;
	cout << rc3(x) << endl;

	return 0;
}
