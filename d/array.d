import std.stdio;
import std.algorithm;

void main() {
	// Unlike C or C++, static array in DLang has different syntax:
	
	/* Can not use varaible to init an array.
	int [10] Ints;
	int dynamicLength;
	write("Enter length here: ");
	// can use ref in readf
	readf(" %s", dynamicLength);
	int [dynamicLength]DInts;
	for (int i = 0; i < dynamicLength; i++) {
		writeln("Default value DInts ", i, " is ", DInts[i]);
	}
	*/

	/* This is also unavaliable because Ints has already initialized
	int [10] Ints;
	int dynamicLength;
	Ints.length = dynamicLength;
	Ints[dynamicLength - 2] = 11;
	writeln("Ints at ", dynamicLength - 2, " is write to ", Ints[dynamicLength - 2]);
	*/

	// This is just how to create a dynamic array.
	int [] array;
	int dynamicLength;
	write("Enter init length: ");
	readf(" %s", dynamicLength);
	array.length = dynamicLength;

	// And you can chenge the length again
	int dstLength = 15;
	array.length = dstLength;
	for (int i = 0; i < dstLength; i++)  {
		array[i] = i + 1;
	}
	writeln("array is updated and its length is set to ", dstLength, " : ", array);
	write("You want to set index 2 to (Enter your wish here):");
	// You can use ref to set the value!
	readf(" %s", array[2]);
	writeln("array is updated to: ", array);

	writeln();

	// Append an element at the end of the dynamic array
	array.length = 0;
	int counter = 0, tmp;
	write("Enter 10 numbers to append: ");
	while (++counter <= 10) {
		readf(" %s", tmp);
		array ~= tmp;
	}
	writeln("array is updated to: ", array);

	writeln();

	write("Which value do you dislike and want to remove it: ");
	readf(" %s", tmp);
	// must import std.algorithm
	// Maybe lambda expression here like JS
	array = array.remove!(x => x == tmp);
	writeln("array is update to: ", array);

	writeln();

	// we can combine some array
	int [10] first = [1, 2, 3, 4, 5, 6, 7, 8, 9, 0];
	int [5] second = [-5, -4, -3, -2, -1];
	int [] combination;
	combination = first ~ second;
	writeln("combine first: ", first, " and second: ", second, " to combination: ", combination);
	combination ~= first;
	writeln("combination combine with first again to: ", combination);

	sort(combination);
	writeln("use sort in std.algorithm to sort combination to: ", combination);
	reverse(combination);
	writeln("and reverse it: ", combination);
}
