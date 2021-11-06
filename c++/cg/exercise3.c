#include<stdio.h>
#include<stdlib.h>
int main()

{
	int *p;
	int *pp;
	int i;
	int m=0;
	int size;
	int b;
	int dsize=0;
	int test=0;
	int a;
 
	printf("How many integers do you want?: ");
 
	while(1) {
		scanf("%d",&size);
		p = (int *)malloc(sizeof(int) * (size-1));
		if(p == NULL) {
			printf("input a smaller value");
			continue;
		}
		break;
	}
 

	for(i = 0; i <= size - 2; i++)
		p[i] = i + 2;
	
	b = size - 1;


	while(1) {
		printf("p[test] = %d\n", p[test]);
		for (i = 1; i < b; i++) {
			if (p[i] % p[test] != 0) {
				dsize++;
				printf("Add dsize, p[i] = %d\n", p[i]);
			}
		}

		pp = (int *)malloc(sizeof(int) * (dsize + 1));
		printf("pre-start: b, dsize = %d, %d\n", b, dsize);
  
		for (i = 0; i < b; i++) {
			if(p[i] % p[test] != 0 || i==test) {
				pp[m] = p[i];
				m++;
			}
		}

		printf("start: b, dsize = %d, %d\n", b, dsize);
     	 
		test++;

		if(test >= (m + 1) / 2)
			break;

		m = 0;
		free(p);
		p = pp;
		b = dsize + 1;

		printf("end: b, dsize = %d, %d\n", b, dsize);
		dsize = 0;
	}

	for(i = 0; i < m; i++) {
		printf("%d\t", pp[i]);
	 }
	printf("\n");

	free(p);
	free(pp);
}
