#ifndef OPERATIONS_H
#define OPERATIONS_H

typedef enum {
    SUCCES = 0,
    INVALID_ARGS,
    NO_RESULT, 
    FAIL
} ErrorCodes;

#define M_PI 3.14159265358979323846

ErrorCodes eLimit(float epsilon, float *e);
ErrorCodes eSeries(float epsilon, float *e);
ErrorCodes eEquation(float epsilon, float *e);

ErrorCodes piLimit(float epsilon, float *pi);
ErrorCodes piSeries(float epsilon, float *pi);
ErrorCodes piEquation(float epsilon, float *pi);

ErrorCodes ln2Limit(float epsilon, float *ln2);
ErrorCodes ln2Series(float epsilon, float *ln2);
ErrorCodes ln2Equation(float epsilon, float *ln2);

ErrorCodes sqrt2Limit(float epsilon, float *sqrt2);
ErrorCodes sqrt2Composition(float epsilon, float *sqrt2);
ErrorCodes sqrt2Equation(float epsilon, float *sqrt2);

ErrorCodes gammaLimit(float epsilon, float *gamma);
ErrorCodes gammaSeries(float epsilon, float *gamma);
ErrorCodes gammaEquation(float epsilon, float *gamma);

void calcConstAndPrint(const char *name,
                 ErrorCodes (*f1)(float, float*),
                 ErrorCodes (*f2)(float, float*),
                 ErrorCodes (*f3)(float, float*),
                 float epsilon);

#endif