#include <stdlib.h>
#include <stdio.h>

int to_int(char * text, int length) {
	int val = 0;
	int addnum = 1;

	// start from last one, 从最低位开始
	for (int i = length - 1; i >= 0; i--) {
		val += text[i] == '0' ? 0 : addnum;
		addnum *= 2;
	}

	/*
	 * 更高效的方法，利用位运算，减少了很多cpu运算负担
	 * int val = 0;
	 * for (int i = 0; i < length; i++) {
	 * 	val |= (text[i] == '0' ? 0 : 1) << i;
	 * }
	 */

	return val;
}

char * to_hex(char * text) {
	char hex_arr[] = "01234567890ABCDEF";

	char * result = (char *)malloc(3 * sizeof(char));
	result[2] = '\0';

	int x = to_int(text, 4), y = to_int(text, 8);
	result[0] = hex_arr[to_int(text, 4)];
	result[1] = hex_arr[to_int(text, 8) & 0xf]; // & 0xf 表示只取后4bit

	return result;
}

int main() {
	char text[9];
	text[8] = '\0'; // 把字符串最后一位设为0
	char buf;
	int ok = 0;

	while (!ok) {
		for (int i = 0;  i < 8; i++) {
			buf = getchar();
			if (buf != '0' && buf != '1') {
				// 错误输入
				printf("Error Input, Please input a 8-bit decimal number:\n");
				rewind(stdin);
				continue;
			}
	
			text[i] = buf;
		}
	
		buf = getchar();
		if (buf != '\n') {
			// 错误位数
			printf("Error Input, Please input a 8-bit decimal number:\n");
			rewind(stdin);
			continue;
		}
		break;
	}

	printf("The binary value %s is %02d in decimal\n", text, to_int(text, 8));
	printf("The binary value %s is %s in hexadecimal\n", text, to_hex(text));
	// 更简单的就直接利用printf
	// printf("Check: The binary value %s is %02X in hexadecimal\n", text, to_int(text, 8));
}
