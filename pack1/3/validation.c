#include "validation.h"

ValidationErrores validateFlag(const char *flag) {
    if (!(flag[0] == '-' || flag[0] == '/')) {
        return INVALID_FLAG;
    }

    char c = flag[1];
    if (!(c == 'q' || c == 'm' || c == 't')) {
        return INVALID_FLAG;
    }

    return VALIDATION_SUCCES;
}

ValidationErrores parsingIntNumber(const char *s, int *res) {
    int sign = 1;
    int i = 0;
    if (s[0] == '-') {
        sign = -1;
        i++;
    }

    *res = 0;

    while (s[i] != '\0') {
        char c = s[i];
        if (c >= '0' && c <= '9') {
            *res = *res * 10 + (c - '0');
        } else {
            return INVALID_NUMBER;
        }

        i++;
    }

    *res *= sign;
    return VALIDATION_SUCCES;
}

ValidationErrores parsingFloatNumber(const char *s, float *res) {
    if (!s || s[0] == '\0') {
        return INVALID_NUMBER;
    }

    float int_part = 0.0;
    int i = 0;

    float sign = 1.0;
    if (s[i] == '-') {
        sign = -1.0;
        i++;
    }

    int found = 0;
    while (s[i] != '.' && s[i] != '\0') {
        char c = s[i];
        if (c >= '0' && c <= '9') {
            int_part = int_part * 10.0 + (c - '0');
            found = 1;
        } else {
            return INVALID_NUMBER;
        }

        i++;
    }

    if (!found && (s[i] == '.' || s[i] == '\0')) {
        return INVALID_NUMBER;
    }

    if (s[i] == '.') {
        i++;
    }

    float fract_part = 0.0;
    float fract_mult = 0.1;
    while (s[i] != '\0') {
        char c = s[i];
        if (c >= '0' && c <= '9') {
            fract_part = fract_part + (c - '0') * fract_mult;
            fract_mult *= 0.1;
        } else {
            return INVALID_NUMBER;
        }

        i++;
    }

    if (s[i] != '\0') {
        return INVALID_NUMBER;
    }

    *res = sign * (int_part + fract_part);
    return VALIDATION_SUCCES;
}