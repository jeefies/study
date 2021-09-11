#include <iostream>
#include <vector>

using namespace std;

vector<int> list;
vector<int> sort(vector<int> list);
void printvec(vector<int> li);

vector<int> sort(vector<int> list) {
	for (int i = 0; i < list.size() - 1; i++) {
		for (int j = 0; j < list.size() -1 - i; j++) {
			int l = list[j], r = list[j + 1];
			if (l > r) {
				list[j + 1] = l;
				list[j] = r;
			}
		}
	}

	return list;
};

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
