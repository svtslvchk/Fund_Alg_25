#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "operations.h"


int equal(const float epsilon, const float a, const float b) {
    return fabs(a - b) < epsilon;
}

OperationStatus max_and_compos_mins(const float a, const float b, const float c, float *res, float *compos) {
    if (a > b && a > c) {
        *res = a;
        *compos = b * c;
    } else if (b > c && b > a) {
        *res = b;
        *compos = a * c;
    } else {
        *res = c;
        *compos = a * b;
    }

    return SUCCES;
}

OperationStatus sum(const float a, const float b, const float c, float *s) {
    *s = a + b + c;
    return SUCCES;
}

OperationStatus equation(const float epsilon, const float a, const float b, const float c, RootsOfEquation *results) {
    if (equal(epsilon, a, 0.0)) {
        if (equal(epsilon, b, 0.0)) {
            if (equal(epsilon, c, 0.0)) {
                results->count = -1;
                return INFINITE_COUNT_ROOTS;
            } else {
                results->count = 0;
                return NO_RESULT;
            }
        }

        results->count = 1;
        results->x1 = results->x2 = -c / b;
        return SUCCES;
    }

    float d = b * b - 4 * a * c;
    if (equal(epsilon, d, 0.0)) {
        results->count = 1;
        results->x1 = results->x2 = -b / (2 * a);
        return SUCCES;
    } else if (d > 0) {
        results->count = 2;
        results->x1 = (-b - sqrt(d)) / (2 * a);
        results->x2 = (-b + sqrt(d)) / (2 * a);
        return SUCCES;
    } else {
        results->count = 0;
        return NO_RESULT;
    }
}

OperationStatus multiplicity(const int a, const int b, bool *mult) {
    if (!b || !a) {
        return INVALID_ARGS;
    }

    *mult = (abs(a) % abs(b) == 0) ? true : false;
    return SUCCES; 
}

OperationStatus triangle(const float epsilon, const float a, const float b, const float c, bool *is_prime_tringle) {
    if (a <= 0 || b <= 0 || c <= 0) {
        return INVALID_ARGS;
    }

    float mx = 0;
    float compos = 0;
    OperationStatus os_max = max_and_compos_mins(a, b, c, &mx, &compos);
    float sq_hyp = mx * mx;
    
    float s = 0;
    OperationStatus ec_sum = sum(a, b, c, &s);

    if (os_max != SUCCES && ec_sum != SUCCES) {
        return INVALID_ARGS;
    }

    float sq_cat = (s - mx) * (s - mx) - 2 * compos;
    if (equal(epsilon, sq_cat, sq_hyp)) {
        *is_prime_tringle = true;
    } else {
        *is_prime_tringle = false;
    }

    return SUCCES;
}

OperationStatus printResult(const float epsilon, const float a, const float b, const float c) {
    RootsOfEquation results;
    OperationStatus os = equation(epsilon, a, b, c, &results);
    printf("Уравнение: (%f)x^2 + (%f)x + (%f) = 0\n", a, b, c);
    if (os == SUCCES) {
        if (results.count == 2) {
            printf("x1 = %f, x2 = %f\n", results.x1, results.x2);
        } else if (results.count == 1) {
            printf("x1 = x2 = %f\n", results.x1);
        }
    } else if (os == NO_RESULT) {
        printf("Уравнение не имеет решений\n");
    } else {
        printf("Уравнение имеет бесконечное множество решений\n");
    }

    return SUCCES;
}

OperationStatus resultEquationPrint(const float epsilon, const float a, const float b, const float c) {
    OperationStatus os1 = printResult(epsilon, a, b, c);
    OperationStatus os2 = printResult(epsilon, a, c, b);
    OperationStatus os3 = printResult(epsilon, b, a, c);
    OperationStatus os4 = printResult(epsilon, b, c, a);
    OperationStatus os5 = printResult(epsilon, c, a, b);
    OperationStatus os6 = printResult(epsilon, c, b, a);

    if (os1 == SUCCES && os2 == SUCCES && os3 == SUCCES && os4 == SUCCES && os5 == SUCCES && os6 == SUCCES) {
        return SUCCES;
    } else {
        return INVALID_ARGS;
    }
}