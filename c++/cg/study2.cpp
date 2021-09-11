#include <iostream>

using namespace std;

int f1(int x) {
	cout << "f1 called" << endl;
	cout << x << endl;
	return x + 2;
}

int f2(int x) {
	cout << "f2 called" << endl;
	cout << x << endl;
	return x + 3;
}

int f3(int x) {
	cout << "f3 called" << endl;
	cout <<  x << endl;
	return x + 4;
}

int (*fs[3])(int) = {f1, f2, f3};
auto fs2 = &fs;
int (*(*fs3)[3])(int) = &fs;

int main() {
	for (int i = 0; i < 3; i++) {
		cout << "in loop return: " << fs[i](i) << endl;
		cout << "in loop again return: " << (*fs2)[i](i) << endl;
	}
}
