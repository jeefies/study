// QuickSort LR ptr
#include <iostream>
#include <vector>

using namespace std;

vector<int> list;
vector<int> sort(vector<int> list);
vector<int> quickSort(vector<int> list, int begin, int end);
void printvec(vector<int> li);

vector<int> sort(vector<int> list) {
	cout << "sort begin" << endl;
	vector<int> result = quickSort(list, 0, list.size() - 1);
	cout << "sort ok" << endl;
	return result;
}

vector<int> quickSort(vector<int> list, int begin, int end) {
	if (begin == end) {
		return list;
	}
	int lp = begin, rp = end;
	int temp = list[begin];
	while (true) {
		if (lp == rp) {break;}
		while (list[rp] >= temp) {
			rp--;
			if (lp == rp) {goto ok;}
		}
		while (list[lp] <= temp) {
			lp++;
			if (lp == rp) {goto ok;}
		}
		if (lp == rp) {break;}
		int _t = list[rp];
		list[rp] = list[lp];
		list[lp] = _t;
	}
	ok:
	if (lp == begin) {
		return list;
	}
	list[begin] = list[rp];
	list[rp] = temp;
	list = quickSort(list, begin, rp);
	list = quickSort(list, rp + 1, end);
	return list;
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

	vector<int> sorted = sort(list);

	FILE * wfile = fopen("sorted.txt", "w");
	for (int i = 0; i < sorted.size(); i++) {
		fprintf(wfile, "%d ", sorted[i]);
	}
	printvec(sorted);
	return 0;
}

void printvec(vector<int> li) {
	for (int i = 0; i < li.size() - 1; i++) {
		cout << li[i] << ",";
	}
	cout << li[li.size() - 1] << endl;
}
