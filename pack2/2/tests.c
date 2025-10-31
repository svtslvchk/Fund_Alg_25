#include <stdio.h>
#include <assert.h>
#include "operations.h"

void test_memchr() {
    char data[] = "abcdef";
    assert(memchr(data, 'c', 6) == data + 2);
    assert(memchr(data, 'z', 6) == NULL);
    printf("memchr: OK\n");
}

void test_memcmp() {
    char a[] = "abc";
    char b[] = "abd";
    assert(memcmp(a, b, 2) == 0);
    assert(memcmp(a, b, 3) < 0);
    printf("memcmp: OK\n");
}

void test_memcpy() {
    char src[] = "hello";
    char dest[10];
    memcpy(dest, src, 6);
    assert(dest[0] == 'h' && dest[4] == 'o');
    printf("memcpy: OK\n");
}

void test_memset() {
    char data[5];
    memset(data, 'x', 4);
    data[4] = '\0';
    assert(data[0] == 'x' && data[3] == 'x');
    printf("memset: OK\n");
}

void test_strlen() {
    assert(strlen("test") == 4);
    assert(strlen("") == 0);
    printf("strlen: OK\n");
}

void test_strchr() {
    const char *s = "abcde";
    assert(strchr(s, 'c') == s + 2);
    assert(strchr(s, 'z') == NULL);
    printf("strchr: OK\n");
}

void test_strrchr() {
    const char *s = "abca";
    assert(strrchr(s, 'a') == s + 3);
    assert(strrchr(s, 'z') == NULL);
    printf("strrchr: OK\n");
}

void test_strncmp() {
    assert(strncmp("abc", "abc", 3) == 0);
    assert(strncmp("abc", "abd", 3) < 0);
    printf("strncmp: OK\n");
}

void test_strncpy() {
    char src[] = "abc";
    char dest[10];
    strncpy(dest, src, 5);
    assert(dest[0] == 'a' && dest[2] == 'c');
    printf("strncpy: OK\n");
}

void test_strncat() {
    char dest[20] = "Hello, ";
    char src[] = "World!";
    strncat(dest, src, 6);
    assert(dest[13] == '\0');
    printf("strncat: OK\n");
}

void test_strcspn() {
    assert(strcspn("abcdef", "x") == 6);
    assert(strcspn("abcdef", "cd") == 2);
    printf("strcspn: OK\n");
}

void test_strpbrk() {
    const char *s = "abcdef";
    assert(strpbrk(s, "xd") == s + 3);
    assert(strpbrk(s, "z") == NULL);
    printf("strpbrk: OK\n");
}

void test_strstr() {
    const char *h = "hello world";
    assert(strstr(h, "world") == h + 6);
    assert(strstr(h, "abc") == NULL);
    printf("strstr: OK\n");
}

void test_strtok() {
    char s[] = "a,b,c";
    char *token = strtok(s, ",");
    assert(token && token[0] == 'a');
    token = strtok(NULL, ",");
    assert(token && token[0] == 'b');
    printf("strtok: OK\n");
}

void test_strerror() {
    char *msg1 = strerror(1);
    char *msg2 = strerror(1000);
    assert(msg1 != NULL);
    assert(strstr(msg2, "Unknown") != NULL);
    printf("strerror: OK\n");
}

int main() {
    printf("Running tests...\n\n");

    test_memchr();
    test_memcmp();
    test_memcpy();
    test_memset();
    test_strlen();
    test_strchr();
    test_strrchr();
    test_strncmp();
    test_strncpy();
    test_strncat();
    test_strcspn();
    test_strpbrk();
    test_strstr();
    test_strtok();
    test_strerror();

    printf("\nAll tests passed successfully.\n");
    return 0;
}
