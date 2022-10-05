import std.stdio;

void main() {
	for (int i = 0; i < 10; i++) {
		writeln("At ", i, i, i, i, i, i);
	}

	// int array[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
	int [10] array = [ 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 ];

	foreach (i, ref v; array) {
		v *= (i + 1);
	}

	foreach (i, v; array) {
		writefln("array[%d]: %d", i, v);
	}
}
