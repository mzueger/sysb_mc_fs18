/**********************************************************
 * SysB: Mikrocontroller                                  *
 *                                                        *
 * String handling                                        *
 *                                                        *
 **********************************************************/

#include <stdint.h>

int8_t stringEquals(const char* str1, const char* str2);

int8_t stringToInt16(const char* str, int16_t* res);
int8_t int16ToString(int16_t value, char* str, int8_t maxl);