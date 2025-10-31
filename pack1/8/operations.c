#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operations.h"
#include "validation.h"

OperationStatus conversionToBase(const ull n, const int base, char **res) {
    ull x = n;

    if (!x) {
        *res = malloc(2);
        if (!(*res)) {
            return MEMORY_ERROR;
        }

        (*res)[0] = '0';
        (*res)[1] = '\0';
        return SUCCESS;
    }

    int count = 0;
    while (x) {
        x /= base;
        count++;
    }

    *res = malloc(count + 1);
    if (!(*res)) {
        return MEMORY_ERROR;
    }

    x = n;
    (*res)[count] = '\0';
    for (int i = count - 1; i >= 0; i--) {
        int temp = x % base;
        (*res)[i] = (temp >= 10) ? ('A' + temp - 10) : (temp + '0');
        x /= base;
    }

    return SUCCESS;
}

OperationStatus findAndConvertMax(const int base, char **result, char **res9, char **res18, char **res27, char **res36) {
    *result = NULL;
    *res9 = NULL;
    *res18 = NULL;
    *res27 = NULL;
    *res36 = NULL;

    int f = 0;

    char buffer[256];
    ull mx = 0;
    while (fgets(buffer, sizeof(buffer), stdin)) {
        if (strcmp(buffer, "Stop\n") == 0 || strcmp(buffer, "Stop") == 0) {
                break;
        }

        ValidationStatus vs = validateNumberWithBase(buffer, base);
        if (vs == INVALID_NUMBER) {
            continue;
        } else {
            f = 1;
        }

        char *new_buffer = buffer;
        while (*new_buffer == '0' && *(new_buffer + 1) != '\0') {
            new_buffer++;
        }

        ull x = strtoull(new_buffer, NULL, base);
        if (x > mx) {
            mx = x;
        }
    }

    OperationStatus os_res = conversionToBase(mx, base, result);
    OperationStatus os9 = conversionToBase(mx, 9, res9);
    OperationStatus os18 = conversionToBase(mx, 18, res18);
    OperationStatus os27 = conversionToBase(mx, 27, res27);
    OperationStatus os36 = conversionToBase(mx, 36, res36);

    if (os9 != SUCCESS || os18 != SUCCESS || os27 != SUCCESS || os36 != SUCCESS || os_res != SUCCESS) {
        return FAIL;
    }

    if (!f) {
        return NOT_FOUND;
    }

    return SUCCESS;
}