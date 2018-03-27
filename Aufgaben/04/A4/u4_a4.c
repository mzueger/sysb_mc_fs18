/*
 * Systemtechnik B: Mikrocontroller
 * 
 * Übung 4, Aufgaben 4
 * String zu Integer (8 Bit)
 * 
 * Testprogramm für den PC, nicht für den AVR!
 */

#include <stdint.h> 
#include <stdio.h>
#include <limits.h>

/**
 * Wandelt einen Null-terminierten String
 * in einen vorzeichenbehafteten 8 Bit
 * Integer.
 * @param str String, muss eine dezimale Zahl repräsentieren
 * @return Repräsentierter Wert oder INT8_MIN im Fehlerfall
 */
int8_t stringToInt8(const char str[]) {
    int8_t i = 0;
    int8_t v = 0;
	int8_t is_negative = 0;
	
	while(str[i] != '\0') {
		if(str[i] == '-') {
			is_negative = 1;
		}
		else if(str[i] >= '0' && str[i] <= '9') {
            v = v * 10 + str[i] - '0';
        }
		else {
			return INT8_MIN;
		}
        i++;
     }
	 if(is_negative) v = -v;
	 return v;
}

int main(void) {
	char str1[] = "123";
	char str2[] = "-9";
	char str3[] = "0";
	char str4[] = "127";
	char str5[] = "-128";
	char str6[] = "abc";
	
	int8_t v1 = stringToInt8(str1);
    int8_t v2 = stringToInt8(str2);
    int8_t v3 = stringToInt8(str3);
    int8_t v4 = stringToInt8(str4);
    int8_t v5 = stringToInt8(str5);
    int8_t v6 = stringToInt8(str6);
	
	if(v1 != 123)  printf("ERROR for str1\n");
	if(v2 != -9)   printf("ERROR for str2\n");
	if(v3 != 0)    printf("ERROR for str3\n");
	if(v4 != 127)  printf("ERROR for str4\n");
	if(v5 != -128) printf("ERROR for str5\n");
	if(v6 != -128) printf("ERROR for str6\n");
	
	printf("%s = %d\n", str1, v1);
	printf("%s = %d\n", str2, v2);
	printf("%s = %d\n", str3, v3);
	printf("%s = %d\n", str4, v4);
	printf("%s = %d\n", str5, v5);
	printf("%s = %d\n", str6, v6);
}
