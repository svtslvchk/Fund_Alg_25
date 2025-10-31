#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <stdbool.h>

typedef enum {
    SUCCES = 0,
    INVALID_ARGS,
    NO_RESULT,
    INFINITE_COUNT_ROOTS
} OperationStatus;

typedef struct {
    int count;
    float x1;
    float x2;
} RootsOfEquation;

OperationStatus equation(const float epsilon, const float a, const float b, const float c, RootsOfEquation *results);
OperationStatus multiplicity(const int a, const int b, bool *mult);
OperationStatus triangle(const float epsilon, const float a, const float b, const float c, bool *is_prime_tringle);
OperationStatus max_and_compos_mins(const float a, const float b, const float c, float *res, float *compos);
OperationStatus sum(const float a, const float b, const float c, float *s);
OperationStatus resultEquationPrint(const float epsilon, const float a, const float b, const float c);

#endif