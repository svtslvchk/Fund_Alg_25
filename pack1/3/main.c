#include "operations.h"
#include "validation.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    char *flag = argv[1];
    ValidationErrores ve_flag = validateFlag(flag);
    if (ve_flag != VALIDATION_SUCCES) {
        printf("Неправильно указан флаг или флг не найден\n");
        return ve_flag;
    }

    switch (flag[1]) {
        case 'q': {
            if (argc != 6) {
                printf("Неверное количество аргументов\n");
                return INVALID_ARGS;
            }

            float a = 0.0, b = 0.0, c = 0.0, epsilon = 0.0;
            ValidationErrores ve_epsilon = parsingFloatNumber(argv[2], &epsilon);
            ValidationErrores ve_a = parsingFloatNumber(argv[3], &a);
            ValidationErrores ve_b = parsingFloatNumber(argv[4], &b);
            ValidationErrores ve_c = parsingFloatNumber(argv[5], &c);

            if (ve_a != VALIDATION_SUCCES || ve_b != VALIDATION_SUCCES || ve_c != VALIDATION_SUCCES || ve_epsilon != VALIDATION_SUCCES) {
                printf("Некорректно переданы аргументы\n");
                return INVALID_ARGS;
            }

            OperationStatus os = resultEquationPrint(epsilon, a, b, c);
            if (os != SUCCES) {
                return INVALID_ARGS;
            }

            break;
        }

        case 'm': {
            if (argc != 4) {
                printf("Неверное количество аргументов\n");
                return INVALID_ARGS;
            }

            int a = 0, b = 0;
            ValidationErrores ve_a = parsingIntNumber(argv[2], &a);
            ValidationErrores ve_b = parsingIntNumber(argv[3], &b);

            if (ve_a != VALIDATION_SUCCES || ve_b != VALIDATION_SUCCES) {
                printf("Некорректно переданы аргументы\n");
                return INVALID_ARGS;
            }

            bool mult;
            OperationStatus os_mult = multiplicity(a, b, &mult);
            if (os_mult != SUCCES) {
                printf("Числа должны быть ненулевыми\n");
                return INVALID_ARGS;
            }

            if (mult) {
                printf("Чило %d кратно %d\n", a, b);
            } else {
                printf("Чило %d не кратно %d\n", a, b);
            }

            break;
        }

        case 't': {
            if (argc != 6) {
                printf("Неверное количсетво аргументов");
                return INVALID_ARGS;
            }

            float a = 0.0, b = 0.0, c = 0.0, epsilon = 0.0;
            ValidationErrores ve_epsilon = parsingFloatNumber(argv[2], &epsilon);
            ValidationErrores ve_a = parsingFloatNumber(argv[3], &a);
            ValidationErrores ve_b = parsingFloatNumber(argv[4], &b);
            ValidationErrores ve_c = parsingFloatNumber(argv[5], &c);

            if (ve_a != VALIDATION_SUCCES || ve_b != VALIDATION_SUCCES || ve_c != VALIDATION_SUCCES || ve_epsilon != VALIDATION_SUCCES) {
                printf("Некорректно переданы аргументы\n");
                return INVALID_ARGS;
            }
            
            bool is_prime_tringle;
            OperationStatus os_tringle = triangle(epsilon, a, b, c, &is_prime_tringle);
            if (os_tringle != SUCCES) {
                printf("Некорректно переданы аргументы\n");
                return INVALID_ARGS;
            } else {
                if (is_prime_tringle) {
                    printf("Значения a=%f, b=%f, c=%f могут являться длинами прямоугольного треугольника\n", a, b, c);
                } else {
                    printf("Значения a=%f, b=%f, c=%f не могут являться длинами прямоугольного треугольника\n", a, b, c);
                }
            }

            break;
        }
    }

    return 0;
}