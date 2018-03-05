#include <stdio.h>

int main(void) {
	printf("Aufgabe 1.1:\n");
	printf("a) 14 >> 1: %d (0x%x)\n", 14 >> 1, 14 >> 1);
	printf("b) 13 << 2: %d (0x%x)\n", 13 << 2, 13 << 2);
	printf("c) 17 & 11: %d (0x%x)\n", 17 & 11, 17 & 11);
	printf("d) 14 | 11: %d (0x%x)\n", 14 | 11, 14 | 11);
	printf("\n");
	
	printf("Aufgabe 1.2:\n");
	printf("a) ~-1:                     %d (0x%x)\n", ~-1, ~-1);
	printf("b) 0x00FF | 0x1234:         %d (0x%x)\n", 0x00ff | 0x1234, 0x00ff | 0x1234);
	printf("c) 0x12345678 & 0x00FF0000: %d (0x%x)\n", 0x12345678 & 0x00FF0000, 0x12345678 & 0x00FF0000);
    printf("d) 0x12345678 | 0x00FF0000: %d (0x%x)\n", 0x12345678 | 0x00FF0000, 0x12345678 | 0x00FF0000);
	printf("e) 0011 0101 & 0000 0001:   %d (0x%x)\n", 0x35 & 0x01, 0x35 & 0x01);
	printf("f) 0011 0101 & 0000 0010:   %d (0x%x)\n", 0x35 & 0x02, 0x35 & 0x02);
    printf("g) 0011 0101 & 0000 0100:   %d (0x%x)\n", 0x35 & 0x04, 0x35 & 0x04);
    printf("g) 0011 0101 & (1 << 5):    %d (0x%x)\n", 0x35 & ( 1 << 5), 0x35 & ( 1 << 5));
	
	printf("Aufgabe 1.3:\n");
	char c; short s; int i;
	
	c = 0xff;
    c = c & ~0x0f;
	printf("a) c == 0x%x (%d)\n", c & 0xff, c & 0xff);
	
	c = 0xff;
    c = c & ~(1 << 7);
	printf("b) c == 0x%x (%d)\n", c & 0xff, c & 0xff);
	
    c = 0;
    c = c | ((1 << 7) | (1 << 3) | (1 << 1));
	printf("c) c == 0x%x (%d)\n", c & 0xff, c & 0xff);
    
    s = 0;
    s = s | ((1 << (8 * sizeof(s) - 1)) | (1 << (8 * sizeof(s) - 5)) | (1 << (8 * sizeof(s) - 7)));
	printf("d) i == 0x%x (%d)\n", s & 0xffff, s & 0xffff);
    
    i = 0;
    i = i | ((1 << (8 * sizeof(i) - 1)) | (1 << (8 * sizeof(i) - 5)) | (1 << (8 * sizeof(i) - 7)));
	printf("e) i == 0x%x (%d)\n", i, i);
	
	return 0;
}
