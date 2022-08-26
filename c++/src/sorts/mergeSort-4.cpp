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

void mergeSort(vector<int> & nums, vector<int> & smallCount, int * indexes, int start, int end, int * tmp) {
	if (start + 1 == end) {
		tmp[start] = start;
		return;
	}
	
	int mid = (start + end) / 2;
	
	mergeSort(nums, smallCount, indexes, start, mid, tmp);
	mergeSort(nums, smallCount, indexes, mid, end, tmp);
	
	// printf("combine left right:"); 
	// printVec(tmp, start, mid); printVec(tmp, mid, end);
	
	int li = start, le = mid, ri = mid, re = end, i = start, ie = end;
	
	// 优化
	// 当 nums[tmp[le - 1]]已经小于等于nums[tmp[ri]]时
	// 左边和右边已经是排好序的状态，就不需要再排了 
	if (nums[tmp[le - 1]] <= nums[tmp[ri]])
		return;
	
	while (li < le && ri < re) {
		if (nums[tmp[li]] <= nums[tmp[ri]]) {
			smallCount[tmp[li]] += ri - mid;
			indexes[i++] = tmp[li++];
		} else {
			indexes[i++] = tmp[ri++];
		}
	}
	
	while (ri < re) indexes[i++] = tmp[ri++];
	while (li < le) smallCount[tmp[li]] += ri - mid, indexes[i++] = tmp[li++];
	
	for (i = start; i < ie; i++) {
		tmp[i] = indexes[i];
	}
	
	// printf("\n\tto "); printVec(tmp, start, end); putchar('\n'); 
}

int * mergeSort(vector<int> & nums, vector<int> & smallCount) {
	// 没有改变原数组， 所以用tmp 
	int * tmp = (int *)malloc(sizeof(int) * nums.size());
	int * indexes = (int *)malloc(sizeof(int) * nums.size());
	mergeSort(nums, smallCount, indexes, 0, nums.size(), tmp);
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
	
	vector<int> smallCount(n);
	int * result = mergeSort(nums, smallCount);
	
	int i;
	for (i = 0; i < n - 1; i++) {
		printf("%d ", result[i]);
	}
	printf("%d\n", result[i]);
	
	printVec(smallCount); putchar('\n');
	
	return 0;
}
