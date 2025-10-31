#include "operations.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

OperationStatus getBase(const char *s, int *base) {
    int mx = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        int value = 0;
        if (!isalnum(s[i])) {
            return FAIL;
        }

        if (isdigit(s[i])) {
            value = s[i] - '0';
        } 

        if (isalpha(s[i])) {
            char c = toupper(s[i]);
            value = c - 'A' + 10;
        }

        if (value > mx) {
            mx = value;
        }
    }

    *base = mx + 1;
    return SUCCESS;
}

int isSeparator(const char c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

OperationStatus convertFile(const char *input_filename, const char *output_filename) {
    FILE *input = fopen(input_filename, "r");
    if (!input) {
        return FILE_ERROR;
    }

    FILE *output = fopen(output_filename, "w");
    if (!output) {
        fclose(input);
        return FILE_ERROR;
    }

    int capacity = 2;
    char *buffer = malloc(capacity);
    if (!buffer) {
        fclose(input);
        fclose(output);
        return MEMORY_ERROR;
    }

    int ch;
    int i = 0;
    int corrupted = 0;
    while ((ch = fgetc(input)) != EOF) {
        char c = (char)ch;
        if (isSeparator(c)) {
            if (i && !corrupted) {
                buffer[i] = '\0';
                int base = 0;
                OperationStatus os = getBase(buffer, &base);
                if (os == SUCCESS) {
                    char *normalized = buffer;
                    while (*normalized == '0' && *(normalized + 1) != '\0') {
                        normalized++;
                    }
                    fprintf(output, "%s %d ", normalized, base);
                    long n = strtol(normalized, NULL, base);
                    fprintf(output, "%ld\n", n);
                }
            }

            i = 0;
            corrupted = 0;
        } else if (isalnum(c)) {
            if (!corrupted) {
                if (i + 1 >= capacity) {
                    capacity *= 2;
                    char *temp = realloc(buffer, capacity);
                    if (!temp) {
                        free(buffer);
                        fclose(input);
                        fclose(output);
                        return MEMORY_ERROR;
                    }

                    buffer = temp;
                }
            

                buffer[i] = c;
                i++;
            }
        } else {
            corrupted = 1;
        }
    }

    if (i && !corrupted) {
        buffer[i] = '\0';
        int base = 0;
        OperationStatus os = getBase(buffer, &base);
        if (os == SUCCESS) {
            char *normalized = buffer;
            while (*normalized == '0' && *(normalized + 1) != '\0') {
                normalized++;
            }
            fprintf(output, "%s %d ", normalized, base);
            long n = strtol(normalized, NULL, base);
            fprintf(output, "%ld\n", n);
        }
    }

    free(buffer);
    fclose(input);
    fclose(output);
    return SUCCESS;
}