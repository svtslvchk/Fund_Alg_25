#include "operations.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test_convertFile();

int main() {
    test_convertFile();
    printf("All tests passed successfully!\n");
    return 0;
}

void test_convertFile() {
    // создаём входной файл
    FILE *f = fopen("tmp_in.txt", "w");
    assert(f != NULL);
    fprintf(f, "1010 F 123\nhello 123 Z9\n0005\n");
    fprintf(f, "000123\n");          
    fprintf(f, "2672672?2782\n"); // некорректное, должно проигнорироваться
    fclose(f);

    // вызываем нашу функцию
    assert(convertFile("tmp_in.txt", "tmp_out.txt") == SUCCESS);

    // создаём эталонный expected.txt
    f = fopen("expected.txt", "w");
    assert(f != NULL);
    fprintf(f, "1010 2 10\n");
    fprintf(f, "F 16 15\n");
    fprintf(f, "123 4 27\n");
    fprintf(f, "hello 25 6873049\n");
    fprintf(f, "Z9 36 1269\n");
    fprintf(f, "5 6 5\n");
    fprintf(f, "123 4 27\n"); // это из "000123"
    fclose(f);

    // сравнение построчно
    FILE *out = fopen("tmp_out.txt", "r");
    FILE *exp = fopen("expected.txt", "r");
    assert(out && exp);

    char line_out[256], line_exp[256];
    while (fgets(line_exp, sizeof(line_exp), exp)) {
        char *got = fgets(line_out, sizeof(line_out), out);
        assert(got != NULL);                     // строка должна существовать
        assert(strcmp(line_exp, line_out) == 0); // строки совпадают
    }

    // убедимся, что в out.txt нет лишнего
    assert(fgets(line_out, sizeof(line_out), out) == NULL);

    fclose(out);
    fclose(exp);

    // очистка
    remove("tmp_in.txt");
    remove("tmp_out.txt");
    remove("expected.txt");
}
