#ifndef VALIDATION_H
#define VALIDATION_H

typedef enum {
    VALIDATION_SUCCES = 0,
    INVALID_FLAG,
    INVALID_ARGS
} ValidationErrores;

ValidationErrores parsingFlagAndFilename(char *s1, char *s2, char *s3, char *flag, char **output_file);

#endif