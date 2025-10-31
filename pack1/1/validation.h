#ifndef VALIDATION_H
#define VALIDATION_H

#include <stdbool.h>
#include "operations.h"

typedef enum {
    VALIDATION_SUCCES = 0,
    VALIDATION_INVALID_FLAG,
    VALIDATION_INVALID_NUMBER
} ValidationStatus;

ValidationStatus validateFlag(const char *flag);
ValidationStatus validateNum(const char *s, ull *r);

#endif