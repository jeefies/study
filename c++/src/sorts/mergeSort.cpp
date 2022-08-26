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

// 利用vector合并返回 
vector<int> & mergeSort(vector<int> & nums, int start, int end, vector<int> & smallCount) {
    // 只有一个元素直接返回
    // 返回它的下标，方便标记smallCount 
    if (start + 1 == end) {
        vector<int> ret(1, start);
        return ret;
    }
    
    vector<int> ret(end - start, 0);
    
    int mid = (start + end) / 2;
    
    // 我们采用左闭右开的写法 ^_^ 
    vector<int> left = mergeSort(nums, start, mid, smallCount);
    vector<int> right = mergeSort(nums, mid, end, smallCount);
    
    // printf("merge "); printVec(left); printf(" and "); printVec(right); putchar('\n');
    
    int li = 0, le = left.size(), ri = 0, re = right.size();
    int i = 0;
    while (li < le && ri < re) {
		// 由于没有改变原数组，所以这里直接用下标对应原数组的值比较
    	// 但是放回数组的值任然是下标，而不是真正的值 
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
    
    // printf("\tto "); printVec(ret); putchar('\n');
    // printf("\tupdate smallCount to "); printVec(smallCount); putchar('\n');
    
    assert(i == end - start);
    
    return ret;
}

// 利用了函数重载的小技巧 
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
