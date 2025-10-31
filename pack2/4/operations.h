#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <stdio.h>   
#include <stddef.h>    
#include <stdarg.h>    
#include <stdlib.h>    
#include <string.h>    
#include <ctype.h>     

typedef enum {
    SUCCESS = 0,
    FAIL,
    MEMORY_ERROR,
    INVALID_NUMBER
} OperationStatus;

typedef struct {
    int value;
    const char *symbol;
} RomanDigit;

OperationStatus romeToInt(const char *str, int *res);
OperationStatus zeckendorfToInt(const char *str, unsigned int *res);
OperationStatus baseTo10(const char *num, int base, char reg, int *res);
int overfscanf(FILE *stream, const char *format, ...);
int oversscanf(char *str, const char *format, ...);

#endif