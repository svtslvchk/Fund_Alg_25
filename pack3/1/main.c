#include "operations.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, r;
    printf("Enter number: ");
    scanf("%d", &n);
    printf("Enter r: ");
    scanf("%d", &r);
    char *res = NULL;
    OperationStatus status = convertToBase(n, r, &res);
    if (status == SUCCESS) {
        printf("Result: %s\n", res);
        free(res);
    } else if (status == MEMORY_ERROR) {
        fprintf(stderr, "Memory allocation error\n");
    } else if (status == INVALID_INPUT) {
        fprintf(stderr, "Invalid input\n");
    } else {
        fprintf(stderr, "Unknow error\n");
    }

    return 0;
}