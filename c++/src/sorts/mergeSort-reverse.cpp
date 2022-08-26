#include <iostream>
#include <vector>
#include <cstdio>

#include <assert.h>

using namespace std;

void printVec(vector<int> & v) {
	printf("["); 
	int i;
	for (i = 0; i < v.size() - 1; i++) {
		printf("%d ", v[i]);
	}
	printf("%d]", v[i]);
}

void printVec(int * v, int left, int right) {
	putchar('[');
	while (left + 1 < right) {
		printf("%d ", v[left++]);
	}
	printf("%d]", v[left]);
}

void mergeSort(vector<int> & nums, vector<int> & leftCount, int * indexes, int start, int end, int * tmp) {
	if (start + 1 == end) {
		tmp[start] = start;
		return;
	}
	
	int mid = (start + end) / 2;
	
	mergeSort(nums, leftCount, indexes, start, mid, tmp);
	mergeSort(nums, leftCount, indexes, mid, end, tmp);
	
	// printf("combine left right:"); 
	// printVec(tmp, start, mid); printVec(tmp, mid, end); putchar('\n');
	
	int li = start, le = mid, ri = mid, re = end, i = start, ie = end;
	
	while (li < le && ri < re) {
		if (nums[tmp[li]] >= nums[tmp[ri]]) {
			indexes[i++] = tmp[li++];
		} else {
			leftCount[tmp[ri]] += le - li;
			indexes[i++] = tmp[ri++];
		}
	}
	
	while (ri < re) indexes[i++] = tmp[ri++];
	while (li < le) leftCount[tmp[li]] += re - ri, indexes[i++] = tmp[li++];
	
	for (i = start; i < ie; i++) {
		tmp[i] = indexes[i];
	}
	
	printf("\tto "); printVec(tmp, start, end); putchar('\n'); 
	printf("\tupdate smallCount to "); printVec(leftCount); putchar('\n');
}

int * mergeSort(vector<int> & nums, vector<int> & leftCount) {
	// 没有改变原数组， 所以用tmp 
	int * tmp = (int *)malloc(sizeof(int) * nums.size());
	int * indexes = (int *)malloc(sizeof(int) * nums.size());
	mergeSort(nums, leftCount, indexes, 0, nums.size(), tmp);
	free(tmp);
	for (int i = 0; i < nums.size(); i++)
		indexes[i] = nums[indexes[i]];
	return indexes;
}

int main() {
	int n;
	scanf("%d", &n);
	
	vector<int> nums(n);
	
	for (int i = 0; i < n; i++) {
		scanf("%d", &nums[i]);
	}
	
	vector<int> leftCount(n);
	int * result = mergeSort(nums, leftCount);
	
	int i;
	for (i = 0; i < n - 1; i++) {
		printf("%d ", result[i]);
	}
	printf("%d\n", result[i]);
	
	printVec(leftCount); putchar('\n');
	
	return 0;
}
