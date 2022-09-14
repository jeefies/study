/*
 * 语义“陷阱”
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * Pointers and Array.
 * - C语言里面就只有一维
 * - 数组的本质是指针
 */
int arr[3] = {0};
int * arr_p = arr;
// sizeof(arr) sizeof(arr_p);

int multi_arr[3][3] = {0};

void pointers() {
	/*
	 * 指针和地址
	 */
	int a[3] = {5, 6, 7};
	
	long a_ptr = (long)&a[1];
	int * a2_ptr = (int *)(a_ptr + sizeof(int));
	/* 
	 * int * a_ptr = a + 1;
	 * int * a2_ptr = a_ptr + 1;
	 */
	
	printf("%d\n", *a2_ptr);
	*a2_ptr = 4;
	// *(a + 2) = 4;
	// a[2] = 4;
	printf("%d\n", a[2]);
	// Qeustion:
	// 	What really dose a[i] means?
}

void two_dimensional_array() {
	int calendar[12][31];
	calendar[4][7] = 10;
	int * p;
	int n;

	// ? calendar[4] means ?
	sizeof(calendar[4]) == sizeof(int) * 31;

	p = calendar[4];
	// p = calendar + 4;
	n = p[7];
	// n = p + 7;
	printf("%d\n", n);
	
	n = calendar[4][7];
	printf("%d\n", n);
	n = *(calendar[4] + 7);
	printf("%d\n", n);
	n = *(*(calendar + 4) + 7);
	printf("%d\n", n);

	int (*monthp)[31];
	monthp = calendar;

	/*
	 * for (int month = 0; month < 12; month++) {
	 * 		for (int day = 0; day < 31; day++)
	 * 			calendar[month][day] = 0;
	 * }
	 */

	for (int (*monthp)[31] = calendar; monthp != calendar + 12; monthp++) {
		for (int * dayp = *monthp; dayp != *monthp + 31; dayp++)
			*dayp = 0;
	}
}

int main() {
	pointers();

	two_dimensional_array();

	int * nums = (int *) malloc (sizeof(int) * 10);
	// sizeof(int) * 10 = 40
	// sizeof(nums) = 40;
	printf("%d\n", sizeof(nums));

	return 0;
}
