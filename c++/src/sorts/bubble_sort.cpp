#include <iostream>
#include <vector>

using namespace std;

vector<int> list;
vector<int> Bsort(vector<int> list);
void printvec(vector<int> li);

vector<int> Bsort(vector<int> list) {
	vector<int> sorted(list.begin(), list.end());

	for (int s = 1; s < sorted.size(); s++) {
		for (int i = 0; i < sorted.size() - s; i++) {
			int l = sorted[i], r = sorted[i + 1];
			if (l > r) {
				sorted[i] = r;
				sorted[i + 1] = l;
			}
		}
	}

	return sorted;
}

int main() {
	FILE * rfile = fopen("unsort.txt", "r");

	if (rfile == NULL) {
		cout << "could not read the datas" << endl;
		return 1;
	}

	while (!feof(rfile)) {
		int i;
		fscanf(rfile, "%d ", &i);
		list.push_back(i);
	}
	printvec(list);

	vector<int> sorted = Bsort(list);

	cout << "sort ok..." << endl;
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
	cout << li[li.size()-1] << endl;
}
