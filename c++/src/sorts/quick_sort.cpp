// QuickSort LR ptr
#include <iostream>
#include <vector>

using namespace std;

vector<int> list;

void printvec(vector<int> & li) {
	for (int i = 0; i < li.size() - 1; i++) {
		cout << li[i] << ",";
	}
	cout << li[li.size() - 1] << endl;
}

void quickSort(vector<int> & list, int begin, int end) {
	if (begin + 1 >= end) {
		return;
	}

	int l = begin, r = end - 1, key = list[begin];
	while (l < r) {
		while (l < r && list[r] >= key) {
			r--;
		}
		list[l] = list[r];

		while (l < r && list[l] <= key) {
			l++;
		}
		list[r] = list[l];
	}
	list[l] = key;
	quickSort(list, begin, l);
	quickSort(list, l + 1, end);
}

void quickSort(vector<int> & list) {
	quickSort(list, 0, list.size());
}

int main() {
	FILE * rfile = fopen("unsort.txt", "r");

	if (rfile == NULL) {
		cout << "Cound not read any datas" << endl;
		return 1;
	}

	while (!feof(rfile)) {
		int i;
		fscanf(rfile, "%d ", &i);
		list.push_back(i);
	}
	
	printvec(list);

	quickSort(list);

	FILE * wfile = fopen("sorted.txt", "w");
	for (int i = 0; i < list.size(); i++) {
		fprintf(wfile, "%d ", list[i]);
	}
	printvec(list);
	return 0;
}

