#ifndef VALIDATION_H
#define VALIDATION_H

typedef enum {
    VALIDATION_SUCCES = 0,
    INVALID_FLAG,
    INVALID_NUMBER
} ValidationErrores;

ValidationErrores validateFlag(const char *flag);
ValidationErrores parsingIntNumber(const char *s, int *res);
ValidationErrores parsingFloatNumber(const char *s, float *res);

#endif