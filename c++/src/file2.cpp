#include <stdio.h>
#include <iostream>

using namespace std;

string *readFully(FILE *fptr);

int main() {
	FILE *fptr;

	fptr = fopen("./start.cpp", "r");

	string content = readFully(fptr);
	for (int i = 0; i < 200; i++) {
		cout << content[i];
	};
	printf("\n");
	return 0;
}

string readFully(FILE *fptr) {
	int size = 0, blocksize = 100;
	char full[] = {};
	while (!feof(fptr)) {
		char x[blocksize] = {};
		fread(x, blocksize, 1, fptr);
		char nfull[size + 100] = {};
		for (int i = 0; i < size; i++) {
			nfull[i] = full[i];
		}
		for (int i = 0; i < 100; i++) {
			nfull[size + i] = x[i];
		}
		size += 100;
		char full[size] = {};
		for (int i = 0; i < size; i++) {
			full[i] = nfull[i];
		}
	}
	return string(full);
}
