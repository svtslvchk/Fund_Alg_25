#ifndef OPERATIONS_H
#define OPERATIONS_h

typedef enum {
    SUCCESS = 0,
    FAIL = 1
} OperationStatus;

int equal(float epsilon, float a, float b);
OperationStatus parsingEpsilon(const char *s, float *res);
float f_a(float x, float epsilon);
float f_b(float x, float epsilon);
float f_c(float x, float epsilon);
float f_d(float x, float epsilon);
OperationStatus trapezoids(float (*f)(float, float), float a, float b, float epsilon, float *res);
#endif