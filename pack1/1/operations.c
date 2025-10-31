#include "operations.h"

OperationStatus multiplicity(const ull x, ull arr[], int *count) {
    if (x > 100 || x == 0) {
        return OPERATION_INVALID_INPUT;
    }

    *count = 0;

    for (ull i = x; i <= 100; i+= x) {
        arr[(*count)++] = i;
    }

    if (!(*count)) {
        return OPERATION_NO_RESULT;
    }

    return OPERATION_SUCCES;
}

OperationStatus isPrimeOrIsComposite(const ull x, bool *is_prime) {
    if (x <= 1) {
        return OPERATION_NO_RESULT;
    }

    for (ull i = 2; i < x; i++) {
        if (x % i == 0) {
            *is_prime = false;
            return OPERATION_SUCCES;
        }
    }

    return OPERATION_SUCCES;
}

OperationStatus conversionTo16(const ull x, char digits16[]) {
    if (!x) {
        digits16[0] = '0';
        digits16[1] = '\0';
        return OPERATION_SUCCES;
    }

    int count = 0;
    ull temp = x;

    while (temp) {
        temp /= 16;
        count++;
    }

    temp = x;

    for (int i = count - 1; i >= 0; i--) {
        ull digit = temp % 16;
        if (digit < 10) {
            digits16[i] = '0' + digit;
        } else {
            digits16[i] = 'A' + digit - 10;
        }

        temp /= 16;
    }

    digits16[count] = '\0';

    return OPERATION_SUCCES;
}

OperationStatus tableOfDeqrees(const ull x, ull table[][10]) {
    if (x > 10 || x <= 0) {
        return OPERATION_INVALID_INPUT;
    }

    for (ull i = 1; i <= 10; i++) {
        ull r = 1;

        for (ull j = 1; j <= x; j++) {
            r *= i;
            table[i - 1][j - 1] = r;
        }
    }

    return OPERATION_SUCCES;
}

OperationStatus calculateSum(const ull x, ull *s) {
    if (x <= 0) {
        return OPERATION_INVALID_INPUT;
    }

    *s = (1 + x) * x / 2;
    return OPERATION_SUCCES;
}

OperationStatus factorial(const ull x, ull *f) {
    if (x > 20) {
        return OPERATION_OVERFLOW;
    }

    *f = 1;

    for (ull i = 2; i <= x; i++) {
        *f *= i;
    }

    return OPERATION_SUCCES;
}