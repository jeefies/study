import std.stdio;

void merge_sort(int[] arr, int[] tmp, ulong l, ulong r) {
	if (l + 1 == r) {
		return;
	}

	ulong mid = (l + r) / 2;

	merge_sort(arr, tmp, l, mid);
	merge_sort(arr, tmp, mid, r);

	ulong li = l, le = mid, ri = mid, re = r, i = l;

	// already in order
	if (arr[le - 1] <= arr[ri]) {
		return;
	}

	while (li != le || ri != re) {
		if (li != le && (ri == re || arr[li] <= arr[ri])) {
			tmp[i++] = arr[li++];
		} else {
			tmp[i++] = arr[ri++];
		}
	}

	for (i = l; i < r; i++) {
		arr[i] = tmp[i];
	}
}

void merge_sort(int[] arr) {
	int [] tmp;
	tmp.length = arr.length;
	merge_sort(arr, tmp, 0, arr.length);
}

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
