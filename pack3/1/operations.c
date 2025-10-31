#include "operations.h"
#include <stdlib.h>

void reverse(char *s, int size) {
    for (int i = 0; i < size / 2; i++) {
        char temp = s[i];
        s[i] = s[size - i - 1];
        s[size - i - 1] = temp;
    }
}

OperationStatus createMask(const int r, int *mask) {
    if (r < 1 || r > 5 || !mask) {
        return INVALID_INPUT;
    }

    *mask = 0;
    for (int i = 0; i < r; i++) {
        *mask = (*mask << 1) | 1;
    }

    return SUCCESS;
}

OperationStatus convertToBase(const int number, const int r, char **res) {
    if (!res || r < 1 || r > 5 || !number) {
        return INVALID_INPUT;
    }
    int mask = 0;
    OperationStatus os_mask = createMask(r, &mask);
    if (os_mask != SUCCESS) {
        return os_mask;
    }

    int n = number;
    int i = 0;
    int capacity = 2;
    *res = malloc(capacity);
    if (!*res) {
        return MEMORY_ERROR;
    }

    while (n) {
        int cur = n & mask;
        char digit;
        if (cur < 10) {
            digit = '0' + cur;
        } else {
            digit = 'A' + (cur - 10);
        }
        if (i >= capacity) {
            capacity *= 2;
            char *temp = realloc(res, capacity);
            if (!temp) {
                free(*res);
                return MEMORY_ERROR;
            }

            *res = temp;
        }

        (*res)[i] = digit;
        i++;
        n = (n >> r);
    }

    *res[i] = '\0';

    reverse(*res, i);
    return SUCCESS;
}