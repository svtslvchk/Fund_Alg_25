#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <stdbool.h>

#define MAX_ITER 100
#define EPSILON 0.00000001

typedef enum {
    SUCCESS = 0,
    INVALID_NUMBER,
    INVALID_BASE,
    FAIL
} OperationsStatus; 

OperationsStatus hasFiniteRepresentation(int base, double fract, bool *res);
OperationsStatus checkFiniteRepresentation(bool **res, int base, int count, ...);

#endif