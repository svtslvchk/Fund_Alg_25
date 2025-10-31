#include "validation.h"
#include <ctype.h>

ValidationStatus validateNumberWithBase(char *s, const int base) {
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == ' ' || s[i] == '\n' || s[i] == '\r' || s[i] == '\t') {
            continue;
        }

        int temp = 0;
        if (isdigit(s[i])) {
            temp = s[i] - '0';
        } else if ('A' <= s[i] && s[i] <= 'Z') {
            temp = s[i] - 'A' + 10;
        } else {
            return INVALID_NUMBER;
        }

        if (temp >= base) {
            return INVALID_NUMBER;
        }
    }

    return VALIDATION_SUCCES;
}