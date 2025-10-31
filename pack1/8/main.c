#include "operations.h"
#include "validation.h"
#include <stdio.h>
#include <stdlib.h>   // для free

int main() {
    printf("Enter the base (2-36):\n");
    int base;
    scanf("%d", &base);
    if (base < 2 || base > 36) {
        fprintf(stderr, "The base was entered incorrectly\n");
        return 1;
    }

    printf("Enter the numbers:\n");

    char *res = NULL;
    char *res9 = NULL;
    char *res18 = NULL;
    char *res27 = NULL;
    char *res36 = NULL;

    OperationStatus os = findAndConvertMax(base, &res, &res9, &res18, &res27, &res36);
    if (os == SUCCESS) {
        printf("Max: %s, Base9: %s, Base 18: %s, Base 27: %s, Base 36: %s\n", res, res9, res18, res27, res36);

        free(res);
        free(res9);
        free(res18);
        free(res27);
        free(res36);

        return 0;
    } else if (os == FAIL) {
        fprintf(stderr, "FAIL\n");

        free(res);
        free(res9);
        free(res18);
        free(res27);
        free(res36);

        return 2;
    } else if (os == MEMORY_ERROR) {
        fprintf(stderr, "Memory allocation error\n");

        free(res);
        free(res9);
        free(res18);
        free(res27);
        free(res36);

        return 3;
    } else {
        fprintf(stderr, "All numbers don't match the base\n");

        free(res);
        free(res9);
        free(res18);
        free(res27);
        free(res36);

        return 4;
    }
}
