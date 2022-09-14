import std.stdio;
import std.range;

void main() {
	int[] array = [1, 2, 3, 4, 5];
	foreach (elem; array) {
		writeln("elem: ", elem);
	}

	foreach (ref mutable; array) {
		mutable *= 2;
	}

	foreach (i, elem; array) {
		writeln("Index ", i, ": ", elem);
	}
	writeln();

	foreach (i, c; "Hello") {
		writeln(i, " : ", c);
	}
	writeln();

	writeln("D语言");
	foreach (i, c; "D语言") {
		writeln('\t', i, " : ", c);
	}
	writeln();

	foreach (c; stride("D语言", 1)) {
		writeln('\t', c);
	}

	foreach (i; 10..16) {
		writeln("Range: ", i);
	}
	writeln();

	/* 
	   The use of foreach_reverse is not common because the range function retro() achieves the same goal.
	   We will see retro() in a later chapter.
	 */
	foreach_reverse (elem; array) {
		writeln("Reversed array: ", elem);
	}
}
