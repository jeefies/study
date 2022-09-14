import std.stdio;

void main() {
	// It's like a map, can dynamic manage the key-val elements.
	int[string] dayIndex = [
		"Mon" : 1,
		"Tues" : 2,
		"Wednes" : 3,
		"Thurs": 4,
		"Fri" : 5,
		"Sat" : 6,
		"Sun" : 7,
	];

	writeln("keys: ", dayIndex.keys, " Mon: ", dayIndex["Mon"]);

	dayIndex.remove("Wednes");
	// writeln(dayIndex["Wednes"]); // RE
	writeln(dayIndex.get("Wednes", -1));

	// This is OK
	dayIndex.clear;
	dayIndex.clear(); // Also does no matter.

	dayIndex["Wen"] = 3;
	writeln(dayIndex, " length: ", dayIndex.length);

	/*
		.length returns the number of key-value pairs.
		.keys returns a copy of all keys as a dynamic array.
		.byKey provides access to the keys without copying them; we will see how .byKey is used in foreach loops in the next chapter.
		.values returns a copy of all values as a dynamic array.
		.byValue provides access to the values without copying them.
		.byKeyValue provides access to the key-value pairs without copying them.
		.rehash may make the array more efficient in some cases, such as after inserting a large number of key-value pairs.
		.sizeof is the size of the array reference (it has nothing to do with the number of key-value pairs in the table and is the same value for all associative arrays).
		.get returns the value if it exists, the default value otherwise.
		.remove removes the specified key and its value from the array.
		.clear removes all elements.
	*/
}
