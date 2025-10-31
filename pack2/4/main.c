#include "operations.h"
#include <stdio.h>

int main(void) {
    int roman = 0;
    unsigned int zeck = 0;
    int basev = 0, baseV = 0;

    printf("Enter a Roman numeral: ");
    if (overfscanf(stdin, "%Ro", &roman) == 1) {
        printf("Roman numeral as int: %d\n", roman);
    } else {
        printf("Failed to read Roman numeral\n");
    }

    printf("Enter a Zeckendorf numeral (binary ending with 1): ");
    if (overfscanf(stdin, "%Zr", &zeck) == 1) {
        printf("Zeckendorf numeral as int: %u\n", zeck);
    } else {
        printf("Failed to read Zeckendorf numeral\n");
    }

    printf("Enter a number in base 16 (lowercase letters) and base 16 (uppercase letters): ");
    if (overfscanf(stdin, "%Cv %CV", &basev, 16, &baseV, 16) == 2) {
        printf("Lowercase base 16 -> %d\n", basev);
        printf("Uppercase base 16 -> %d\n", baseV);
    } else {
        printf("Failed to read base numbers\n");
    }

    int num;
    char str[64];
    float fl;
    char ch;

    printf("Enter int, string, float, char (space-separated): ");
    if (overfscanf(stdin, "%d %s %f %c", &num, str, &fl, &ch) == 4) {
        printf("You entered: num=%d str=%s fl=%.2f ch=%c\n", num, str, fl, ch);
    } else {
        printf("Failed to read standard inputs\n");
    }

    return 0;
}
