/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Merge sort from Leetcode 101
 */

#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <vector>
#include <array>
#include <string>
#include <algorithm>
#include <cstring>

using namespace std;

void mergeSort(vector<int> & nums, int l, int r, vector<int> & tmp) {
	if (l + 1 >= r) return;

	int mid = l + (r - l) / 2;
	mergeSort(nums, l, mid, tmp);
	mergeSort(nums, mid, r, tmp);

	int li = l, ri = mid, i = l;
	while (li < mid || ri < r) {
		if (ri >= r || (li < mid && nums[li] <= nums[ri])) {
			tmp[i++] = nums[li++];
		} else {
			tmp[i++] = nums[ri++];
		}
	}

	for (i = l; i < r; i++) {
		nums[i] = tmp[i];
	}
}

void mergeSort(vector<int> & nums) {
	vector<int> tmp (nums.size());

	mergeSort(nums, 0, nums.size(), tmp);
}

void printvec(vector<int> & li) {
	for (int i = 0; i < li.size() - 1; i++) {
		cout << li[i] << ",";
	}
	cout << li[li.size() - 1] << endl;
}

int main() {
	FILE * rfile = fopen("unsort.txt", "r");

	if (rfile == NULL) {
		cout << "Cound not read any datas" << endl;
		return 1;
	}

	vector<int> nums;
	while (!feof(rfile)) {
		int i;
		fscanf(rfile, "%d ", &i);
		nums.push_back(i);
	}
	
	printvec(nums);

	mergeSort(nums);

	FILE * wfile = fopen("sorted.txt", "w");
	for (int i = 0; i < nums.size(); i++) {
		fprintf(wfile, "%d ", nums[i]);
	}
	printvec(nums);
	return 0;
}
