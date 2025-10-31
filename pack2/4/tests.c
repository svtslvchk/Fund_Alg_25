#include "operations.h"
#include <stdio.h>
#include <assert.h>

void test_overfscanf(void) {
    printf("=== test_overfscanf ===\n");
    FILE *f = fopen("input.txt", "w");
    fprintf(f, "XIV 1011 1a FF\n"); 
    fclose(f);

    f = fopen("input.txt", "r");
    int rome = 0, basev = 0, baseV = 0;
    unsigned int zeck = 0;

    int r = overfscanf(f, "%Ro %Zr %Cv %CV", &rome, &zeck, &basev, 16, &baseV, 16);
    fclose(f);

    printf("rome=%d zeck=%u basev=%d baseV=%d (read=%d)\n",
           rome, zeck, basev, baseV, r);

    assert(rome == 14);
    assert(zeck == 4);
    assert(basev == 26); 
    assert(baseV == 255); 
    assert(r == 4);
}

void test_oversscanf(void) {
    printf("=== test_oversscanf ===\n");

    const char *input = "XIV 1011 1a FF";
    int rome = 0, basev = 0, baseV = 0;
    unsigned int zeck = 0;

    int r = oversscanf((char*)input, "%Ro %Zr %Cv %CV", &rome, &zeck, &basev, 16, &baseV, 16);

    printf("rome=%d zeck=%u basev=%d baseV=%d (read=%d)\n",
           rome, zeck, basev, baseV, r);

    assert(rome == 14);
    assert(zeck == 4);
    assert(basev == 26);
    assert(baseV == 255);
    assert(r == 4);
}

void test_standard_overfscanf() {
    FILE *f = fopen("input.txt", "w+");
    fprintf(f, "123 abc 4.56 c");
    rewind(f);

    int num;
    char str[16];
    float fl;
    char ch;

    int n = overfscanf(f, "%d %s %f %c", &num, str, &fl, &ch);

    printf("num=%d str=%s fl=%.2f ch=%c (read=%d)\n", num, str, fl, ch, n);
    assert(num == 123);
    assert(strcmp(str, "abc") == 0);
    assert((int)(fl * 100) == 456);
    assert(ch == 'c');
    assert(n == 4);

    fclose(f);
}

void test_standard_oversscanf() {
    char buf[] = "321 test 7.89 Z";
    int num;
    char str[16];
    float fl;
    char ch;

    int n = oversscanf(buf, "%d %s %f %c", &num, str, &fl, &ch);

    printf("num=%d str=%s fl=%.2f ch=%c (read=%d)\n", num, str, fl, ch, n);
    assert(num == 321);
    assert(strcmp(str, "test") == 0);
    assert((int)(fl * 100) == 789);
    assert(ch == 'Z');
    assert(n == 4);
}

void test_mismatch_format() {
    printf("=== test_mismatch_format ===\n");

    const char *input = "12 hell 12";
    int a = 0, b = 0;

    int n = oversscanf((char *)input, "%d hello %d", &a, &b);
    printf("oversscanf read=%d a=%d b=%d\n", n, a, b);
    assert(n == 1); 

    FILE *tmp = tmpfile();
    fputs("12 hell 12", tmp);
    rewind(tmp);
    a = b = 0;
    n = overfscanf(tmp, "%d hello %d", &a, &b);
    printf("overfscanf read=%d a=%d b=%d\n", n, a, b);
    assert(n == 1);
    fclose(tmp);
}

int main(void) {
    printf("=== Running all tests ===\n\n");
    test_overfscanf();
    test_oversscanf();
    test_standard_overfscanf();
    test_standard_oversscanf();
    test_mismatch_format();
    printf("\n=== All tests passed successfully ===\n");
    return 0;
}
