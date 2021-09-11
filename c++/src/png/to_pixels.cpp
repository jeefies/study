#include <vector>
#include <iostream>
#include "lodepng.h"

using std::vector;
using std::cout;
using std::endl;

int decodeOneStep(const char* filename) {
	vector<unsigned char> image;
	unsigned width, height;

	unsigned error = lodepng::decode(image, width, height, filename);

	if (error) {
		cout << "decode error" << endl;
		return 1;
	}

	cout << image.size();

	for (long unsigned int size = 0; size < image.size();) {
		cout << size << ' ';
		for (int time = 0; time < 4; time++) {
			cout << (unsigned)image[size] << ' ';
			size++;
		}
		cout << endl;
	}

	return 0;
}

int main() {
	const char* filename = "test.png";

	decodeOneStep(filename);
	return 0;
}
