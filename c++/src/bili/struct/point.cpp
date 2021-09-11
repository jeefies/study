#include <iostream>
#include <string>

using std::cout;
using std::string;
using std::endl;

struct Point {
	int a;
	int b;
	string str;
};

int main(int argc, char* argv[]) {
	// C:
	// Point pt = {1, 2}
	Point pt {1, 2, "string cpp"};
	cout << pt.a << ", " << pt.b << endl;
	cout << pt.str << endl;
	return 0;
}
