// Quick Sort
#include <iostream>
#include <vector>

using namespace std;

vector<int> list;
vector<int> sort(vector<int> list);
vector<int> quickSort(vector<int> li, int begin, int end);
void printvec(vector<int> li);

vector<int> sort(vector<int> list) {
	return quickSort(list, 0, list.size() - 1);
};

vector<int> quickSort(vector<int> li, int begin, int end) {
	if (end <= begin) {return li;}

	int l = begin, r = end;
	int temp = li[begin];

	while (true) {
		while (li[r] >= temp) {
			if (r == l) {goto ok;}
			r--;
		}

		while (li[l] <= temp) {
			if (r == l) {goto ok;}
			l++;
		}
		int _temp = li[l];
		li[l] = li[r];
		li[r] = _temp;
	}
	ok:
	li[begin] = li[l];
	li[l] = temp;

	if (end - begin == 1) {return li;}

	li = quickSort(li, begin, l - 1);
	li = quickSort(li, l + 1, end);

	return li;
}

int main() {
	FILE * rfile = fopen("unsort.txt", "r");

	if (rfile == NULL) {
		cout << "Could Not Read any datas" << endl;
		return 1;
	}

	while (!feof(rfile)) {
		int i;
		fscanf(rfile, "%d ", &i);
		list.push_back(i);
	}
	printvec(list);

	vector<int> sorted = sort(list);

	printvec(sorted);
	FILE * wfile = fopen("sorted.txt", "w");
	for (int i = 0; i < sorted.size(); i++) {
		fprintf(wfile, "%d ", sorted[i]);
	}
	return 0;
}

void printvec(vector<int> li) {
	for (int i = 0; i < li.size() - 1; i++) {
		cout << li[i] << ",";
	}
	cout << li[li.size() - 1] << endl;
}
