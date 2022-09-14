/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

int print(int nums[], int length) {
	for (int i = 0; i < length; i++)
		printf("%d ", nums[i]);
	return 0;
}

int main(int argc, char * argv[]) {
	int nums[4] = {1, 2, 3, 4};
	print(nums, 4);

	for (int i = 0; i < argc; i++)
		printf("%s", argv[i]);
}
