// Insertion Sort
#include <iostream>
#include <vector>

using namespace std;

vector<int> list;
vector<int> sort(vector<int> list);
void printvec(vector<int> li);

vector<int> sort(vector<int> list) {
	for (int i = 1; i < list.size(); i++) {
		int temp = list[i];
		for (int j = i - 1; j >= 0; j--) {
			if (list[j] <= temp) {
				list.insert(list.begin() + j + 1, temp);
				list.erase(list.begin() + i + 1);
				goto next;
			}
		}
		
		list.insert(list.begin(), temp);
		list.erase(list.begin() + i + 1);
		next:
		continue;
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
