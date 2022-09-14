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

/*
[0, n) // 左闭右开区间

int a[10];

// wrong
for (int i = 1; i <= 10; i++)
	a[i] = i;

// right
int i;
for (i = 0; i != 10; i++) {
	a[i] = i;
}
*/

int main(int argc, char *argv[])
{
	int i = 0, a[11];
	printf("a %p, i %p\n", a + 11, &i);
	for (i = 0; i <= 11; i++) {
		a[i] = 0;
	}

	// 16 <= x < 38
	// 16 <= x < 16
	//

	foreach (i; 0 .. 10)
}
