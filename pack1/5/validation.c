#include "validation.h"
#include <string.h>
#include <stdlib.h>

ValidationErrores parsingFlagAndFilename(char *s1, char *s2, char *s3, char *flag, char **output_file) {
    if (s2[0] != '-' && s2[0] != '/') {
        return INVALID_FLAG;
    }
    int i = 1;



    if (s2[i] == 'n') {
        i++;
        if (!s3) {
            return INVALID_ARGS;
        }

        *output_file = s3;
    } else {
        int size = strlen(s1) + 5;
        *output_file = malloc(size);
        if (!(*output_file)) {
            return INVALID_ARGS;
        }

        strcpy(*output_file, "out_");
        strcat(*output_file, s1);
    }

    if (!(s2[i] == 'd' || s2[i] == 'i' || s2[i] == 's' || s2[i] == 'a')) {
        return INVALID_FLAG;

    } else {
        *flag = s2[i];
    }

    if (s2[1] != 'n' && s3) {
        return INVALID_ARGS;
    }

    return VALIDATION_SUCCES;
}
