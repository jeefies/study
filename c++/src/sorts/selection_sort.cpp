// QuickSort, One Ptr
#include <iostream>
#include <vector>

using std::cout;
using std::vector;
using std::endl;

void printvec(vector<int> li);
vector<int> Qsort(vector<int> list, vector<int> sorted);

vector<int> list;

vector<int> Qsort(vector<int> list) {
	vector<int> sorted;
	cout << "sorting" << endl;

	for (int i = 0; i < list.size(); i++) {
		int temp = list[i];
		for (int j = i + 1; j < list.size(); j++) {
			if (list[j] < temp) {
				list[i] = list[j];
				list[j] = temp;
				temp = list[i];
			}
		}
		sorted.push_back(temp);
	}

	return sorted;
}

int main() {
	FILE * rfile = fopen("unsort.txt", "r");
	if (rfile == NULL) {
		cout << "Failed to read the datas" << endl;
		return 1;
	}

	cout << "scanning the datas:" << endl;
	while (!feof(rfile)) {
		int i;
		fscanf(rfile, "%d ", &i);
		list.push_back(i);
	}
	printvec(list);

	vector<int> sorted = Qsort(list);

	FILE * wfile = fopen("sorted.txt", "w");
	for (int i = 0; i < sorted.size(); i++) {
		fprintf(wfile, "%d ", sorted[i]);
	}
	fclose(wfile);
	printvec(sorted);
	return 0;
}

void printvec(vector<int> li) {
	for (int i = 0; i < li.size(); i++) {
		cout << li[i] << ',';
	}
	cout << "\b\n";
}
