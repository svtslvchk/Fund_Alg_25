#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <stdbool.h>

typedef unsigned long long ull;

typedef enum {
    OPERATION_SUCCES = 0,
    OPERATION_INVALID_INPUT,
    OPERATION_NO_RESULT,
    OPERATION_OVERFLOW
} OperationStatus;
 
#define MAX_MULT 100
#define MAX_16 16
#define MAX_ROWS 10
#define MAX_COLS 10

OperationStatus multiplicity(const ull x, ull arr[], int *count);
OperationStatus isPrimeOrIsComposite(const ull x, bool *is_prime);
OperationStatus conversionTo16(const ull x, char digits16[]);
OperationStatus tableOfDeqrees(const ull x, ull table[][10]);
OperationStatus calculateSum(const ull x, ull *s);
OperationStatus factorial(const ull x, ull *f);

#endif