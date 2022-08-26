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
 
// 使用vector会比int*慢，而且内存占用更多 
// smallCount记录右侧严格比自己小的数 
int * mergeSort(vector<int> & nums, int start, int end, vector<int> & smallCount) {
	int * ret = (int *)malloc(sizeof(int) * (end - start));
	// 只有一个元素直接返回
	// 返回它的下标，方便标记smallCount 
	if (start + 1 == end) {
		ret[0] = start;
		return ret;
	}
	
	int mid = (start + end) / 2;
	
	// 我们采用左闭右开的写法 ^_^ 
	int * left = mergeSort(nums, start, mid, smallCount);
	int * right = mergeSort(nums, mid, end, smallCount);
	
	int li = 0, le = mid - start, ri = 0, re = end - mid;
	int i = 0, ie = end - start;
	while (li < le && ri < re) {
		if (nums[left[li]] <= nums[right[ri]]) {
			smallCount[left[li]] += ri;
			ret[i++] = left[li++];
		} else {
			ret[i++] = right[ri++];
		}
	}
	
	while (ri < re) ret[i++] = right[ri++];
	// 无论是在哪里更新left，都需要加上ri
	// ri不仅是表示right数组当前的下标
	// 也表示比left[li]小且以前没有记录过的数的个数 
	while (li < le) smallCount[left[li]] += ri, ret[i++] = left[li++];

	// 释放内存空间	
	free(left); free(right);
	
	return ret;
}

// 利用了函数重载的小技巧 
vector<int> mergeSort(vector<int> & nums, vector<int> & smallCount) {
	int * sorted = mergeSort(nums, 0, nums.size(), smallCount);
	vector<int> ret(sorted, sorted + nums.size());
	free(sorted);
	return ret;
}

int main() {
	int n;
	scanf("%d", &n);
	
	vector<int> nums(n);
	
	for (int i = 0; i < n; i++) {
		scanf("%d", &nums[i]);
	}
	
	vector<int> smallCount(n);
	vector<int> result = mergeSort(nums, smallCount);
	
	// printVec(result); putchar('\n');
	
	int i;
	for (i = 0; i < n - 1; i++) {
		printf("%d ", nums[result[i]]);
	}
	printf("%d\n", nums[result[i]]);
	
	printVec(smallCount); putchar('\n');
	
	return 0;
}
