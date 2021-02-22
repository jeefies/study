#include <iostream>
#include <vector>

using namespace std;

vector<int> list;
vector<int> sort(vector<int> list);
void printvec(vector<int> li);

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

	for (int i = 0; i < list.size(); i++) {
		cout << list[i] << ",";
	}

	vector<int> sorted = sort(list);

	FILE * wfile = fopen("sorted.txt", "w");
	for (int i = 0; i < sorted.size(); i++) {
		cout << list[i] << ",";
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
