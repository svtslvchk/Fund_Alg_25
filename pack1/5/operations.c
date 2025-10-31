#include "operations.h"
#include <stdio.h>
#include <stdlib.h>

int isArabicDigit(char c) {
    return '0' <= c && c <= '9';
}

OperationsStatus removeArabicDigits(const char *input_filename, const char *output_filename) {
    FILE *input = fopen(input_filename, "r");
    if (!input) {
        return FAIL;
    }

    FILE *output = fopen(output_filename, "w");
    if (!output) {
        fclose(input);
        return FAIL;
    }

    char c;
    while ((c = fgetc(input)) != EOF) {
        if (!isArabicDigit(c)) {
            fputc(c, output);
        }
    }

    fclose(input);
    fclose(output);

    return SUCCES;
}

OperationsStatus countLatinLettersinLines(const char *input_filename, const char *output_filename) {
    FILE *input = fopen(input_filename, "r");
    FILE *output = fopen(output_filename, "w");
    if (!input || !output) {
        return FAIL;
    }

    char line[256];
    while (fgets(line, sizeof(line), input)) {
        int count = 0;
        for (int i = 0; line[i] != '\n' && line[i]; i++) {
            if (isalpha(line[i])) {
                count++;
            } 
        }

        fprintf(output, "%d\n", count);
    }

    fclose(input);
    fclose(output);
    return SUCCES;
}

OperationsStatus notLatinArabicSpace(const char *input_filename, const char *output_filename) {
    FILE *input = fopen(input_filename, "r");
    FILE *output = fopen(output_filename, "w");
    if (!input || !output) {
        return FAIL;
    }

    char line[256];
    while ((fgets(line, sizeof(line), input))) {
        char c;
        int i = 0;
        int count = 0;
        while ((c = line[i++]) != '\n' && c != '\0') {
            if (!(('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z')) && !(isArabicDigit(c)) && !(c == ' ')) {
                count++;
            }
        }

        fprintf(output, "%d\n", count);
    }

    fclose(input);
    fclose(output);
    return SUCCES;
}

OperationsStatus notArabicToASCII(const char *input_filename, const char *output_filename) {
    FILE *input = fopen(input_filename, "r");
    FILE *output = fopen(output_filename, "w");
    if (!input || !output) {
        return FAIL;
    }

    char c;
    while ((c = fgetc(input)) != EOF) {
        if (c == '\n') {
            fputc(c, output);
        }
        
        if (!isArabicDigit(c)) {
            int x = (int)c;
            fprintf(output, "%X", x);
        } else {
            fputc(c, output);
        }
    }

    fclose(input);
    fclose(output);
    return SUCCES;
}