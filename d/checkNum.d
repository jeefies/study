import std.stdio;
import std.math;

void main() {
	if (isNaN(double.nan)) {
		writeln("double.nan IsNaN");
	} else {
		writeln("No nan...");
	}
}
