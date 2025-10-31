#include <stdio.h>
#include <stdlib.h>
#include "prime.h"

int main() {
    int t;
    // ввод
    printf("Введите количество запросов:\n");
    scanf("%d", &t);
    printf("Введите %d чисел\n", t);

    ull *results = NULL;
    PrimeStatus *statuses = NULL;

    PrimeStatus ps = findPrimes(t, &results, &statuses);
    if (ps == NO_RESULT) {
        printf("Нет результата\n");
        return ps;
    }

    if (ps == INVALID_ARGS) {
        printf("Некорректно переданы аргументы\n");
        return ps;
    }

    if (ps == MEMORY_ERROR) {
        printf("Ошибка выделения памяти\n");
        return ps;
    }

    for (int i = 0; i < t; i++) {
        PrimeStatus s = statuses[i];

        if (s == SUCCES) {
            printf("%llu\n", results[i]);
        } else {
            printf("Fail!\n");
        }
    }

    return 0;
}