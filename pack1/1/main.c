#include <stdio.h>
#include "operations.h"
#include "validation.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Неверное количсетво аргументов\n");
        return 1;
    }
    
    ull x;
    ValidationStatus vs = validateNum(argv[1], &x);

    if (vs == VALIDATION_INVALID_NUMBER) {
        printf("Ошибка! неверно введено число\n");
        return vs;
    }

    vs = validateFlag(argv[2]);
    if (vs == VALIDATION_INVALID_FLAG) {
        printf("Ошибка! Неверно введен флаг\n");
        return vs;
    }

    char flag = argv[2][1];
    OperationStatus os;

    switch(flag) {
        case 'h': {
            ull arr[MAX_MULT];
            int count;
            os = multiplicity(x, arr, &count);

            if (os == OPERATION_SUCCES) {
                printf("Числа, кратные %llu:\n", x);
                for (int i = 0; i < count; i++) {
                    printf("%llu ", arr[i]);
                }

                printf("\n");
            } else if (os == OPERATION_NO_RESULT) {
                printf("Для числа %llu нет натуральных чисел, кратных ему\n", x);
                return os;
            } else {
                printf("Недопустимое значение\n");
                return os;
            }

            break;
        }

        case 'p': {
            bool is_prime = true;
            os = isPrimeOrIsComposite(x, &is_prime);

            if (os == OPERATION_SUCCES) {
                if (is_prime) {
                    printf("Число %llu является простым\n", x);
                } else {
                    printf("Число %llu является составным\n", x);
                }
                
            } else {
                printf("Число %llu не является ни простым, ни составным\n", x);
            }

            break;
        }

        case 's': {
            char digits16[MAX_16];
            os = conversionTo16(x, digits16);

            if (os == OPERATION_SUCCES) {
                for (int i = 0; digits16[i] != '\0'; i++) {
                    printf("%c ", digits16[i]);
                }

                printf("\n");
            }

            break;
        }

        case 'e': {
            ull table[x][MAX_COLS];
            os = tableOfDeqrees(x, table);

            if (os == OPERATION_INVALID_INPUT) {
                printf("Ошибка! Значение должно быть в перелах от 1 до 10\n");
            } else {
                printf("%12s", "base \\ exp");

                for (ull i = 1; i <= x; i++) {
                    printf("%12llu", i);
                }

                printf("\n");

                for (ull i = 1; i <= 10; i++) {
                    printf("%12llu", i);
                    for (ull j = 1; j <= x; j++) {
                        printf("%12llu", table[i - 1][j - 1]);
                    }

                    printf("\n");
                }
            }

            break;
        }

        case 'a': {
            ull s;
            os = calculateSum(x, &s);

            if (os == OPERATION_INVALID_INPUT) {
                printf("Ошибка! Число должно быть натуральным\n");
            } else {
                printf("Сумама чисел от 1 до %llu: %llu\n", x, s);
            }

            break;
        }

        case 'f': {
            ull f;
            os = factorial(x, &f);

            if (os == OPERATION_OVERFLOW) {
                printf("Ошибка! Выберите число от 0 до 20\n");
            } else {
                printf("%llu! = %llu\n", x, f);
            }

            break;
        }
    }

    return 0;
}