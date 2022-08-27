import std.stdio;

void main() {
	// list some good named characters
	wchar pi = '\&pi;';
	wchar [11] arrows = [ '\&larr;', '\&rarr;', '\&uarr;', '\&darr;', '\&harr;', '\&crarr;', '\&lArr;', '\&rArr;', '\&uArr;', '\&dArr;', '\&hArr;' ];
	writeln("Pi: ", pi);
	writeln("Arrows: ", arrows);

	writeln("Forall: \&forall;");
	writeln("Exist: \&exist;");

	writeln("empty: \&empty;");
	writeln("isIn: \&isin;");
	writeln("notIn: \&notin;");
	writeln("ni: \&ni;");

	writeln("prod: \&prod;");
	writeln("sum: \&sum;");

	writeln("inf: \&infin;");

	writeln("radic: \&radic;3");
}
