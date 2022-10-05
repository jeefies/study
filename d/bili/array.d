import std.stdio;
import std.array;
import core.exception;

void main() {
	// int arr[10];
	/*
	int [10] arr;
	for (int i = 0; i < 10; i++) {
		readf(" %d", arr[i]);
	}

	writeln(arr);
	*/

	/*
	int length = 10;
 	readf("%d", length);

	int [] dynamic_arr;
	dynamic_arr.length = length;
	// int [length] dynamic_arr;

	foreach_reverse (ref int i; dynamic_arr) {
		readf(" %d", i);
	}

	writeln(dynamic_arr);
	*/

	// associative array
	// value_type [key_type] associative_array_name;
	int [string] dayIndex = [
		"Mon" : 1,
		"Tues" : 2,
		"Thurs" : 4,
	];

	writeln(dayIndex["Tues"]);
	try {
		writeln(dayIndex["Wednes"]);
	} catch(RangeError e) {
		writeln("Key \"Wednes\" does not exist");
	}

	if ("Thurs" in dayIndex) {
		dayIndex.remove("Thurs");
		try {
			writeln(dayIndex["Thurs"]);
		} catch(RangeError e) {
			writeln("Key thurs removed");
		}

	} else {
		writeln("Key thurs does not exist");
	}
}
