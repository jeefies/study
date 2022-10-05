import std.stdio;

void main() {
    double zero = 0;
    double infinity = double.infinity;

	writeln("type of infinity: ", double.stringof);
	writeln("size of double: ", double.sizeof);

    writeln("any expression with nan: ", double.nan + 1);
    writeln("zero / zero            : ", zero / zero);
    writeln("zero * infinity        : ", zero * infinity);
    writeln("infinity / infinity    : ", infinity / infinity);
    writeln("infinity - infinity    : ", infinity - infinity);
}
