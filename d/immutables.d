import std.stdio;
import std.random;

void print(int[] nums) {
	foreach (i, v; nums) {
		writefln("%d: %d", i, v);
	}
}

void main() {
    const      inferredType = 0;
    const int  explicitType = 1;
    const(int) fullType     = 2;

    writeln(typeof(inferredType).stringof);
    writeln(typeof(explicitType).stringof);
    writeln(typeof(fullType).stringof);

	enum arr = [1, 5, 4, 7];
	print(arr);

	print([1, 5, 4, 7]); // Memeory is allocated when running.
}
