/*
 * Systemtechnik B: Mikrocontroller
 * 
 * Übung 4, Aufgaben 5
 * String zu Integer (16 Bit)
 * 
 * Testprogramm für den PC, nicht für den AVR!
 */

#include <stdint.h> 
#include <stdio.h>
#include <limits.h>

/**
 * Wandelt einen Null-terminierten String
 * in einen vorzeichenbehafteten 16 Bit
 * Integer.
 * @param str String, muss eine dezimale Zahl repräsentieren
 * @return Repräsentierter Wert oder INT16_MIN im Fehlerfall
 */
int16_t stringToInt16(const char str[]) {
    int8_t i = 0;
    int16_t v = 0;
	int8_t is_negative = 0;
	
	while(str[i] != '\0') {
		if(str[i] == '-') {
			is_negative = 1;
		}
		else if(str[i] >= '0' && str[i] <= '9') {
            v = v * 10 + str[i] - '0';
        }
		else {
			return INT16_MIN;
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
	char str4[] = "32767";
	char str5[] = "-32768";
	char str6[] = "abc";
	
	int16_t v1 = stringToInt16(str1);
    int16_t v2 = stringToInt16(str2);
    int16_t v3 = stringToInt16(str3);
    int16_t v4 = stringToInt16(str4);
    int16_t v5 = stringToInt16(str5);
    int16_t v6 = stringToInt16(str6);
	
	if(v1 != 123)    printf("ERROR for str1\n");
	if(v2 != -9)     printf("ERROR for str2\n");
	if(v3 != 0)      printf("ERROR for str3\n");
	if(v4 != 32767)  printf("ERROR for str4\n");
	if(v5 != -32768) printf("ERROR for str5\n");
	if(v6 != -32768) printf("ERROR for str6\n");
	
	printf("%s = %d\n", str1, v1);
	printf("%s = %d\n", str2, v2);
	printf("%s = %d\n", str3, v3);
	printf("%s = %d\n", str4, v4);
	printf("%s = %d\n", str5, v5);
	printf("%s = %d\n", str6, v6);
}
