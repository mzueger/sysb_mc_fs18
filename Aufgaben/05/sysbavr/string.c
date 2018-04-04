/**********************************************************
 * SysB: Mikrocontroller                                  *
 *                                                        *
 * String handling                                        *
 *                                                        *
 **********************************************************/

#include <string.h>

/**
 * @brief Compares two null terminated strings
 * 
 * @return 1 if the strings are equal, 0 if not
 */
int8_t stringEquals(const char* str1, const char* str2) {
	if(!str1 || !str2) return 0;
	while(*str1 == *str2) {
		if(*str1 == '\0') {
			return 1;
		}
		str1++; str2++;
	}
	return 0;
}

/**
 * @brief Converts a string into a 16 bit integer
 * 
 * @param str string to convert, has to be null terminated
 * @param res pointer where the result should be written
 * @return 0 on success or a negative error code
 */
int8_t stringToInt16(const char* str, int16_t* res) {
	int8_t i = 0;
	int16_t v = 0;
	int8_t is_negative = 0;
    if(!str || !res) return -1;
	
	while(str[i] != '\0') {
		if(str[i] == '-') {
			is_negative = 1;
		}
		else {
			v = (v << 3) + (v << 1) + str[i] - '0';
		}
        i++;
     }
	 if(is_negative && v > 0) v = -v;
     *res = v;
	 return 0;
}

/**
 * @brief Converts a 16 bit integer into a string
 * 
 * @param value integer to convert
 * @param str buffer where the string will be written to
 * @param maxl length of the buffer (max. length for the string)
 * @return 0 on success or a negative error code
 */
int8_t int16ToString(int16_t value, char* str, int8_t maxl) {
	if(!str) return -1;
	
	int8_t i = 0;
	int8_t is_negative = value < 0;
	value = is_negative ? -value : value;
	
	do {
		str[i++] = value % 10 + '0';
		value = value / 10;
		if(i >= maxl - 1) {
			return -2;
		}
	} while(value != 0);
	
	if(is_negative) str[i++] = '-';
	
	str[i] = '\0';
	
	for(int8_t j = 0; j < i / 2; j++) {
		str[j] ^= str[i - j - 1];
		str[i - j - 1] ^= str[j];
		str[j] ^= str[i - j - 1];
	}
	return i;
}
