#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<int> list;
vector<int> sort(vector<int> list);
void printvec(vector<int> li);

vector<int> sort(vector<int> list) {
	cout << "sort start\n";

	int loop = 1;
	while (1 == 1) {
		cout << 0;
		vector<int> one(list.size());
		int bottles[10][list.size()];
		int count[10] = {0,0,0,0,0,0,0,0,0,0};
		int not0 = 0;
		cout << 1;
		for (int i = 0; i < list.size(); i++) {
			int o = list[i] % (10 * loop);
			if (o != 0) {
				not0++;
			}
			bottles[o][count[o]] = i;
			count[o] += 1;
			cout << "2";
		}
		cout << 3;
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < count[i]; j++) {
				one.push_back(bottles[i][j]);
			}
			cout << 4;
		}
		list = one;
		cout << 5;
		if (not0 == 0) {break;}
		loop++;
	}

	return list;
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
