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

OperationStatus intToRome(int num, char **out);
OperationStatus zeckendorf(unsigned int n, char **out);
OperationStatus intToBase(int num, int base, char reg, char **res);
OperationStatus baseTo10(const char *num, int base, char reg, char **res);
OperationStatus dumpBytes(const unsigned char *bytes, size_t size, char **res);
int overfprintf(FILE *stream, const char *format, ...);
int oversprintf(char *str, const char *format, ...);

#endif