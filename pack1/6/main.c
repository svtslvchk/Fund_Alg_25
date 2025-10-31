#include "operations.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Incorrect number of arguments\n");
        return 1;
    }

    float epsilon = 0.0;
    OperationStatus os_eps = parsingEpsilon(argv[1], &epsilon);
    if (os_eps == FAIL) {
        fprintf(stderr, "Invalid number\n");
        return 1;
    }

    float a = 0.0, b = 0.0, c = 0.0, d = 0.0;

    OperationStatus os_a = trapezoids(&f_a, 0.0, 1.0, epsilon, &a);
    OperationStatus os_b = trapezoids(&f_b, 0.0, 1.0, epsilon, &b);
    OperationStatus os_c = trapezoids(&f_c, 0.0, 1.0, epsilon, &c);
    OperationStatus os_d = trapezoids(&f_d, 0.0, 1.0, epsilon, &d);

    if (os_a == FAIL || os_b == FAIL || os_c == FAIL || os_d == FAIL) {
        fprintf(stderr, "FAIL\n");
        return 1;
    } else {
        printf("The integral a): %f\n", a);
        printf("The integral b): %f\n", b);
        printf("The integral c): %f\n", c);
        printf("The integral d): %f\n", d);

        return 0;
    }
}