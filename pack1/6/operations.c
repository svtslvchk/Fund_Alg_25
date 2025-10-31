#include "operations.h"
#include <math.h>

OperationStatus parsingEpsilon(const char *s, float *res) {
    if (!s || s[0] == '\0') {
        return FAIL;
    }

    float int_part = 0.0;
    int i = 0;

    float sign = 1.0;
    if (s[i] == '-') {
        sign = -1.0;
        i++;
    }

    int found = 0;
    while (s[i] != '.' && s[i] != '\0') {
        char c = s[i];
        if (c >= '0' && c <= '9') {
            int_part = int_part * 10.0 + (c - '0');
            found = 1;
        } else {
            return FAIL;
        }

        i++;
    }

    if (!found && (s[i] == '.' || s[i] == '\0')) {
        return FAIL;
    }

    if (s[i] == '.') {
        i++;
    }

    float fract_part = 0.0;
    float fract_mult = 0.1;
    while (s[i] != '\0') {
        char c = s[i];
        if (c >= '0' && c <= '9') {
            fract_part = fract_part + (c - '0') * fract_mult;
            fract_mult *= 0.1;
        } else {
            return FAIL;
        }

        i++;
    }

    if (s[i] != '\0') {
        return FAIL;
    }

    *res = sign * (int_part + fract_part);
    return SUCCESS;
}

int equal(float epsilon, float a, float b) {
    return fabs(a - b) < epsilon;
}

float f_a(float x, float epsilon) {
    if (equal(epsilon, x, 0.0)) {
        return 1.0;
    }

    return log(1.0 + x) / x;
}

float f_b(float x, float epsilon) {
    (void)epsilon;
    return exp(-(x * x / 2));
}

float f_c(float x, float epsilon) {
    if (equal(epsilon, x, 1.0)) {
        return 0.0;
    }

    return -log(1.0 - x);
}

float f_d(float x, float epsilon) {
    (void)epsilon;
    return pow(x, x);
}

OperationStatus trapezoids(float (*f)(float, float), float a, float b, float epsilon, float *res) {
    int n = 2;
    float h = (b - a) / n;
    float I = h * (0.5 * (f(b, epsilon) + f(a, epsilon)) + f(a + h, epsilon));
    float I1 = 0.0;
    do {
        I1 = I;
        n *= 2;
        h = (b - a) / n;
        I = 0.5 * (f(a, epsilon) + f(b, epsilon));
        for (int i = 1; i < n; i++) {
            I += f(a + h * i, epsilon);
        }

        I *= h;
    } while (fabs(I - I1) > epsilon);

    *res = I;
    return SUCCESS;
}