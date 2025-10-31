#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <stdio.h>

#define WIDTH 80
#define MAX_BUFFER 10000 

typedef enum {
    SUCCESS = 0,
    FAIL
} OperationStatus;

OperationStatus process_file(const char *input_path, const char *output_path);

#endif
