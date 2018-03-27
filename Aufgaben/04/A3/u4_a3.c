/*
 * Systemtechnik B: Mikrocontroller
 * 
 * Übung 4, Aufgabe 3
 * Strings vergleichen
 * 
 * Testprogramm für den PC, nicht für den AVR!
 */

#include <stdint.h> 
#include <stdio.h>

/**
 * Zwei Strings vergleichen.
 * @param str1 String 1
 * @param str2 String 2
 * @return 1 wenn beide Strings identisch, sonst 0
 */
int8_t stringEquals(const char str1[], const char str2[]) {
    int i = 0;
    while(str1[i] == str2[i]) {
        if(str1[i] == '\0') {
            return 1;
        }
        i++;
    }
    return 0;
}

int main(void) {

    char str1[] = "Hello";
    char str2[] = "HEllo";
    char str3[] = "Hello, World";

    int error = 0;

    if(!stringEquals(str1, str1)) {
        error++;
        printf("ERROR in test 1\n");
    }
    
    if(stringEquals(str1, str2)) {
        error++;
        printf("ERROR in test 2\n");
    }
    
    if(stringEquals(str1, str3)) {
        error++;
        printf("ERROR in test 3\n");
    }

    printf("Test finished with %d error(s)\n", error);

    return 0;
}
