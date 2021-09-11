// Selection Sort
#include <iostream>
#include <vector>

using namespace std;

vector<int> list;
vector<int> sort(vector<int> list);
void printvec(vector<int> li);

vector<int> sort(vector<int> list) {
	vector<int> res(list.begin(), list.end());

	for (int i = 0; i < list.size(); i++) {
		int temp = res[i], min = i;
		for (int j = i+1; j < list.size(); j++) {
			if (res[j] < temp) {
				temp = res[j];
				min = j;
			}
		}
		res[min] = res[i];
		res[i] = temp;
	}

	return res;
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
