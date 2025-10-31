#include "operations.h"
#include <stdio.h>

int main() {
    int n, r;
    printf("Enter number: \n");
    scanf("%d", &n);
    printf("Enter r: \n");
    scanf("%d", &r);
    char *res;
    OperationStatus status = convertToBase(n, r, &res);
    if (status == SUCCESS) {
        while (*res) {
            printf("%c", *res);
            res++;
        }

        printf("\n");
    }

    return 0;
}