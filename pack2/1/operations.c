#include "operations.h"
#include <stdarg.h>
#include <stdlib.h>
#include <math.h>

OperationsStatus hasFiniteRepresentation(int base, double fract, bool *res) {
    if (!res) {
        return FAIL;
    }

    if (base < 2) {
        *res = false;
        return INVALID_BASE;
    }

    if (fract <= 0 || fract >= 1) {
        *res = false;
        return INVALID_NUMBER;
    }

    double x = fract;
    double prev = -1.0;
    for (int i = 0; i < MAX_ITER; i++) {
        x *= base;
        x -= (int)x;
        if (x < 0) {
            x = 0.0;
        }

        if (fabs(x - prev) < EPSILON) {
            *res = false;
            return SUCCESS;
        }

        prev = x;

        if (fabs(x) < EPSILON) {
            *res = true;
            return SUCCESS;
        }
    }

    *res = false;
    return SUCCESS;
}

OperationsStatus checkFiniteRepresentation(bool **res, int base, int count, ...) {
    if (count <= 0) {
        return FAIL;
    }

    va_list args;
    va_start(args, count);

    *res = malloc(count * sizeof(bool));
    if (!*res) {
        va_end(args);
        return FAIL;
    }

    for (int i = 0; i < count; i++) {
        double fract = va_arg(args, double);
        bool result;
        OperationsStatus os = hasFiniteRepresentation(base, fract, &result);
        (*res)[i] = result;

        if (os != SUCCESS) {
            va_end(args);
            return os;
        }
    }

    va_end(args);
    return SUCCESS;
    
}