#include <stdio.h>
#include "operations.h"

int main(void) {
    char input[512], output[512];

    printf("Enter input file path: ");
    if (scanf("%511s", input) != 1) return 1;
    printf("Enter output file path: ");
    if (scanf("%511s", output) != 1) return 1;

    if (process_file(input, output) != SUCCESS) {
        fprintf(stderr, "Processing failed\n");
        return 1;
    }

    return 0;
}
