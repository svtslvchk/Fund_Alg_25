#ifndef OPERATIONS_H
#define OPERATIONS_H

typedef enum {
    SUCCESS = 0,
    MEMORY_ERROR,
    INVALID_INPUT
} OperationStatus;

OperationStatus createMask(const int r, int *mask);
OperationStatus convertToBase(const int number, const int r, char **res);

#endif