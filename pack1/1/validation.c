#include "validation.h"
#include <string.h>
#include <ctype.h>

ValidationStatus validateFlag(const char *flag) {
    if (strlen(flag) != 2 || !flag) {
        return VALIDATION_INVALID_FLAG;
    }

    if (flag[0] != '-' && flag[0] != '/') {
        return VALIDATION_INVALID_FLAG;
    }

    if (!(flag[1] == 'h' || flag[1] == 'p' || flag[1] == 's' || flag[1] == 'e' || flag[1] == 'a' || flag[1] == 'f')) {
        return VALIDATION_INVALID_FLAG;
    }

    return VALIDATION_SUCCES;

}

ValidationStatus validateNum(const char *s, ull *r) {
    if (!s || s[0] == '\0') {
        return VALIDATION_INVALID_NUMBER;
    }

    int i = 0;
    if (s[i] == '-') {
        return VALIDATION_INVALID_NUMBER;
    }

    if (s[i] == '\0') {
        return VALIDATION_INVALID_NUMBER;
    }

    ull val = 0;
    while (s[i] != '\0') {
        if (!(s[i] >= '0' && s[i] <= '9')) {
            return VALIDATION_INVALID_NUMBER;
        }

        val = val * 10 + (s[i] - '0');
        i++;
    }

    *r = val;
    return VALIDATION_SUCCES;
}