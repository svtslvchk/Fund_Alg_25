#include "operations.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    bool *results = NULL;
    int base = 10;
    int count = 4;
    double d[] = {0.5, 0.25, 0.2, 1.0/3};

    OperationsStatus os = checkFiniteRepresentation(&results, base, count, d[0], d[1], d[2], d[3]);

    if (os == INVALID_BASE) {
        fprintf(stderr, "Incorrect base!\n");
        return 1;
    } else if (os == INVALID_NUMBER) {
        fprintf(stderr, "Invalid number!\n");
        free(results);
        return 1;
    } else if (os == FAIL) {
        fprintf(stderr, "FAIL!\n");
        free(results);
        return 1;
    }

    if (os == SUCCESS) {
        for (int i = 0; i < count; i++) {
            printf("%g - %s\n", d[i], (results[i]) ? "конечное": "бесконечное");
        }
    }

    free(results);
    return 0;
}
