#include <stdio.h>
#include <stdlib.h>
#include "operations.h"

int main(void) {
    overfprintf(stdout,
        "Число в римской системе: %Ro\n"
        "Цекендорфово представление: %Zr\n"
        "int=255 base=16: %Cv\n"
        "Перевод из 2 в 10: %to\n"
        "Дамп int: %mi\n\n",
        1987, 25u, 255, 16, "1101", 2, -123);

    char buffer[512];
    oversprintf(buffer,
        "Rome: %Ro | Zeckendorf: %Zr | Base16: %CV | toBase10: %to",
        42, 12u, 255, 16, "1010", 2);

    printf("oversprintf результат:\n%s\n", buffer);

    return 0;
}
