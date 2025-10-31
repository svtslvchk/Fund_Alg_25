#include "operations.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Incorrect number of args\n");
        return 1;
    }

    char *input_filename = argv[1];
    char *output_filename = argv[2];
    OperationStatus os = convertFile(input_filename, output_filename);
    if (os == SUCCESS) {
        printf("SUCCESS\n");
        return 0;
    } else if (os == MEMORY_ERROR) {
        fprintf(stderr, "Memory allocation error\n");
        return 2;
    } else if (os == FILE_ERROR) {
        fprintf(stderr, "File opening error\n");
        return 3;
    } else {
        return 1;
    }
}