#include <stdio.h>
int main() {
	char a = 0x3a;
	char b = 0x5b;
	char c = 0xc2;
	
	char x1 = a & b;
	char x2 = a | b;
	char x3 = a ^ b;
	char x4 = ~a;
	char x5 = a << 2;
	char x6 = b >> 2;
	char x7 = c >> 2;

	printf("%x, %x, %x, %x, %x, %x, %x", x1, x2, x3, x4, x5, x6, x7);

	return 0;
}