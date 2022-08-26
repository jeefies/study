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

// ����vector�ϲ����� 
vector<int> & mergeSort(vector<int> & nums, int start, int end, vector<int> & smallCount) {
    // ֻ��һ��Ԫ��ֱ�ӷ���
    // ���������±꣬������smallCount 
    if (start + 1 == end) {
        vector<int> ret(1, start);
        return ret;
    }
    
    vector<int> ret(end - start, 0);
    
    int mid = (start + end) / 2;
    
    // ���ǲ�������ҿ���д�� ^_^ 
    vector<int> left = mergeSort(nums, start, mid, smallCount);
    vector<int> right = mergeSort(nums, mid, end, smallCount);
    
    // printf("merge "); printVec(left); printf(" and "); printVec(right); putchar('\n');
    
    int li = 0, le = left.size(), ri = 0, re = right.size();
    int i = 0;
    while (li < le && ri < re) {
		// ����û�иı�ԭ���飬��������ֱ�����±��Ӧԭ�����ֵ�Ƚ�
    	// ���ǷŻ������ֵ��Ȼ���±꣬������������ֵ 
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
    
    // printf("\tto "); printVec(ret); putchar('\n');
    // printf("\tupdate smallCount to "); printVec(smallCount); putchar('\n');
    
    assert(i == end - start);
    
    return ret;
}

// �����˺������ص�С���� 
vector<int> mergeSort(vector<int> & nums, vector<int> & smallCount) {
    return mergeSort(nums, 0, nums.size(), smallCount);
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
