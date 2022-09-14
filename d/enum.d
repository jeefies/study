import std.stdio;
import std.traits;

enum Days : int { monday = 0, tuesday, thursday };

void main() {
	foreach (day; EnumMembers!Days) {
		writefln("%s: %d", day, day);
	}

	enum num = 1;
	// num = 10;  Error: cannot modify constant num
}
