#include "operations.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

void test_intToRome(void) {
    printf("=== test_intToRome ===\n");
    char *buf = NULL;

    assert(intToRome(1987, &buf) == SUCCESS);
    printf("1987 -> %s\n", buf);
    assert(strcmp(buf, "MCMLXXXVII") == 0);
    free(buf);

    assert(intToRome(4, &buf) == SUCCESS);
    printf("4 -> %s\n", buf);
    assert(strcmp(buf, "IV") == 0);
    free(buf);

    assert(intToRome(944, &buf) == SUCCESS);
    printf("944 -> %s\n", buf);
    assert(strcmp(buf, "CMXLIV") == 0);
    free(buf);
}

void test_zeckendorf(void) {
    printf("\n=== test_zeckendorf ===\n");
    char *buf = NULL;

    assert(zeckendorf(0, &buf) == SUCCESS);
    printf("0 -> %s\n", buf);
    assert(strcmp(buf, "1") == 0);
    free(buf);

    assert(zeckendorf(1, &buf) == SUCCESS);
    printf("1 -> %s\n", buf);
    assert(strcmp(buf, "101") == 0);
    free(buf);

    assert(zeckendorf(2, &buf) == SUCCESS);
    printf("2 -> %s\n", buf);
    assert(strcmp(buf, "011") == 0);
    free(buf);

    assert(zeckendorf(5, &buf) == SUCCESS);
    printf("5 -> %s\n", buf);
    assert(strcmp(buf, "00011") == 0);
    free(buf);

    assert(zeckendorf(10, &buf) == SUCCESS);
    printf("10 -> %s\n", buf);
    assert(strcmp(buf, "010011") == 0);
    free(buf);

    assert(zeckendorf(25, &buf) == SUCCESS);
    printf("25 -> %s\n", buf);
    assert(strcmp(buf, "10100011") == 0);
    free(buf);

    assert(zeckendorf(55, &buf) == SUCCESS);
    printf("55 -> %s\n", buf);
    assert(strcmp(buf, "0000000011") == 0);
    free(buf);
}

void test_intToBase(void) {
    printf("\n=== test_intToBase ===\n");
    char *res = NULL;

    assert(intToBase(255, 16, 'v', &res) == SUCCESS);
    printf("255 base16 -> %s\n", res);
    assert(strcmp(res, "ff") == 0);
    free(res);

    assert(intToBase(255, 16, 'V', &res) == SUCCESS);
    printf("255 base16 upper -> %s\n", res);
    assert(strcmp(res, "FF") == 0);
    free(res);

    assert(intToBase(10, 2, 'v', &res) == SUCCESS);
    printf("10 base2 -> %s\n", res);
    assert(strcmp(res, "1010") == 0);
    free(res);

    assert(intToBase(10, 100, 'v', &res) == SUCCESS);
    printf("10 base100 (invalid base -> default 10) -> %s\n", res);
    assert(strcmp(res, "10") == 0);
    free(res);
}

void test_baseTo10(void) {
    printf("\n=== test_baseTo10 ===\n");
    char *res = NULL;

    assert(baseTo10("ff", 16, 'v', &res) == SUCCESS);
    printf("ff base16 -> %s\n", res);
    assert(strcmp(res, "255") == 0);
    free(res);

    assert(baseTo10("FF", 16, 'V', &res) == SUCCESS);
    printf("FF base16 -> %s\n", res);
    assert(strcmp(res, "255") == 0);
    free(res);

    assert(baseTo10("1010", 2, 'v', &res) == SUCCESS);
    printf("1010 base2 -> %s\n", res);
    assert(strcmp(res, "10") == 0);
    free(res);

    OperationStatus st = baseTo10("XYZ", 16, 'v', &res);
    printf("XYZ base16 -> status=%d (ожидаем INVALID_NUMBER)\n", st);
    assert(st == INVALID_NUMBER);

    st = baseTo10(NULL, 10, 'v', &res);
    printf("NULL -> status=%d (ожидаем FAIL)\n", st);
    assert(st == FAIL);
}

void test_dumpBytes(void) {
    printf("\n=== test_dumpBytes ===\n");
    int num = 5;
    char *res = NULL;
    assert(dumpBytes((const unsigned char *)&num, sizeof(num), &res) == SUCCESS);
    printf("int=5 dump -> %s\n", res);
    free(res);
}

void test_overfprintf_oversprintf(void) {
    printf("\n=== test_overfprintf / oversprintf ===\n");
    char buffer[512];

    oversprintf(buffer,
        "Rome: %Ro | Zeckendorf: %Zr | Base16: %Cv | toBase10: %to",
        42, 25u, 255, 16, "1010", 2);
    printf("oversprintf -> %s\n", buffer);

    oversprintf(buffer,
        "UpperBase: %CV | ToUpper: %TO",
        255, 16, "FF", 16);
    printf("oversprintf upper -> %s\n", buffer);

    printf("overfprintf -> ");
    overfprintf(stdout,
        "Rome: %Ro | Zeckendorf: %Zr | Base16: %Cv | toBase10: %to\n",
        1987, 25u, 255, 16, "1010", 2);
}

void test_overfprintf_errors(void) {
    printf("\n=== test_overfprintf_errors ===\n");
    char buf[128];

    int r = oversprintf(buf, "%Qq", 123);
    printf("invalid format %%Qq -> %d\n", r);
}

void test_standard_flags(void) {
    printf("\n=== test_standard_flags ===\n");

    char buf[256];

    oversprintf(buf, "int=%d, hex=%x, str=%s, float=%.2f, char=%c",
                42, 255, "hello", 3.14159, 'A');

    printf("oversprintf -> %s\n", buf);
    assert(strcmp(buf, "int=42, hex=ff, str=hello, float=3.14, char=A") == 0);

    printf("overfprintf -> ");
    overfprintf(stdout, "int=%d, hex=%x, str=%s, float=%.2f, char=%c\n",
                42, 255, "hello", 3.14159, 'A');
}

int main(void) {
    printf("=== Running all function tests ===\n\n");
    test_intToRome();
    test_zeckendorf();
    test_intToBase();
    test_baseTo10();
    test_dumpBytes();
    test_overfprintf_oversprintf();
    test_overfprintf_errors();
    test_standard_flags();
    printf("\n=== All tests completed successfully ===\n");
    return 0;
}
