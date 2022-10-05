#include <stdio.h>
#include <limits.h>


int main(int argc, char *argv<::>) <%
	int arr<:3:> = <%1, 2, 3%>;

	int a<:3:><:3:> = <%
		<%1, 2, 3%>,
		<%4, 5, 6%>,
		<%7, 8, 9%>,
	%>;

	// arrayName<:index:>
	// index<:arrayName:>
	printf("%d\n", 2<:arr:>);

	printf("%d\n", 0<:0<:a:>:>);

	int time = -3;
	while (time++ < 0) {
		printf("Time passed!\n");
	}

	char * s = "Hello ........................"
	"...........................................................\n";

	printf(s);

	// short < int < long
	// 2 <= short <= int <= long
	//
	// 1Byte 不一定等于 8bits
	printf("%d\n", CHAR_BIT);

	return 0;
%>
