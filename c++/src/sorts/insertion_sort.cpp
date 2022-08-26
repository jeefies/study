// Insertion Sort
#include <iostream>
#include <vector>

using namespace std;

void printvec(vector<int> li) {
	for (int i = 0; i < li.size() - 1; i++) {
		cout << li[i] << ",";
	}
	cout << li[li.size() - 1] << endl;
}

void insertionSort(vector<int> & nums) {
	for (int i = 0; i < nums.size(); i++) {
		for (int j = i; j > 0 && nums[j] < nums[j - 1]; --j) {
			swap(nums[j], nums[j - 1]);
		}
	}
};

int main() {
	FILE * rfile = fopen("unsort.txt", "r");

	if (rfile == NULL) {
		cout << "Could Not Read any datas" << endl;
		return 1;
	}
	
	vector<int> nums;
	while (!feof(rfile)) {
		int i;
		fscanf(rfile, "%d ", &i);
		nums.push_back(i);
	}
	printvec(nums);

	insertionSort(nums);

	printvec(nums);
	FILE * wfile = fopen("sorted.txt", "w");
	for (int i = 0; i < nums.size(); i++) {
		fprintf(wfile, "%d ", nums[i]);
	}
	return 0;
}

