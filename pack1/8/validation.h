#ifndef VALIDATION_H
#define VALIDATION_H

typedef enum {
    VALIDATION_SUCCES = 0,
    INVALID_NUMBER,
    INVALID_BASE
} ValidationStatus;

ValidationStatus validateNumberWithBase(char *s, const int base);

#endif