import sort, std.stdio;


void main() {
	int length;
	write("please eater the number of numbers you entered: ");
	scanf(" %d", &length);
	
	int [] array;
	array.length = length;
	for (int i = 0; i < length; i++) {
		scanf(" %d", &array[i]);
	}

	merge_sort(array);

	writeln(array);
}
