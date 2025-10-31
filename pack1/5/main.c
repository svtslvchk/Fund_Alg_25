#include "validation.h"
#include "operations.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (!(argc == 3 || argc == 4)) {
        printf("Некорректное количество аргументов\n");
        return INVALID_ARGS;
    }

    char *input_filename = argv[1];
    char flag;
    char *output_filename;
    char *s = (argc == 4) ? argv[3] : NULL;
    ValidationErrores ve = parsingFlagAndFilename(input_filename, argv[2], s, &flag, &output_filename);

    if (ve == VALIDATION_SUCCES) {
        switch (flag) {
            case 'd': {
                OperationsStatus os = removeArabicDigits(input_filename, output_filename);
                if (os != SUCCES) {
                    printf("FAIL\n");
                    return os;
                }

                break;
            }

            case 'i': {
                OperationsStatus os = countLatinLettersinLines(input_filename, output_filename);
                if (os != SUCCES) {
                    printf("FAIL!\n");
                    return os;
                }

                break;
            }

            case 's': {
                OperationsStatus os = notLatinArabicSpace(input_filename, output_filename);
                if (os != SUCCES) {
                    printf("FAIL!\n");
                    return os;
                }

                break;
            }

            case 'a': {
                OperationsStatus os = notArabicToASCII(input_filename, output_filename);
                if (os != SUCCES) {
                    printf("FAIL!\n");
                    return os;
                }

                break;
            }
        }
    } else {
        printf("Некорректный флаг\n");
    }

    return 0;

}