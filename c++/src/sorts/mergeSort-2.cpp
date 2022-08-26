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
 
// ʹ��vector���int*���������ڴ�ռ�ø��� 
// smallCount��¼�Ҳ��ϸ���Լ�С���� 
int * mergeSort(vector<int> & nums, int start, int end, vector<int> & smallCount) {
	int * ret = (int *)malloc(sizeof(int) * (end - start));
	// ֻ��һ��Ԫ��ֱ�ӷ���
	// ���������±꣬������smallCount 
	if (start + 1 == end) {
		ret[0] = start;
		return ret;
	}
	
	int mid = (start + end) / 2;
	
	// ���ǲ�������ҿ���д�� ^_^ 
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
	// ���������������left������Ҫ����ri
	// ri�����Ǳ�ʾright���鵱ǰ���±�
	// Ҳ��ʾ��left[li]С����ǰû�м�¼�������ĸ��� 
	while (li < le) smallCount[left[li]] += ri, ret[i++] = left[li++];

	// �ͷ��ڴ�ռ�	
	free(left); free(right);
	
	return ret;
}

// �����˺������ص�С���� 
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
