#include "operations.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdarg.h>

OperationStatus intToRome(int num, char **out) {
    if (num < 0) {
        return INVALID_NUMBER;
    }

    if (!out) {
        return FAIL;
    }

    RomanDigit romanTable[] = {
        {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"},
        {100, "C"},  {90, "XC"},  {50, "L"},  {40, "XL"},
        {10, "X"},   {9, "IX"},   {5, "V"},   {4, "IV"}, {1, "I"}
    };

    size_t cap = 64;
    char *res = calloc(cap, 1);
    if (!res) {
        return MEMORY_ERROR;
    }

    for (int i = 0; i < 13; i++) {
        while (num >= romanTable[i].value) {
            size_t need = strlen(res) + strlen(romanTable[i].symbol) + 1;
            if (need > cap) {
                cap *= 2;
                char *tmp = realloc(res, cap);
                if (!tmp) {
                    free(res);
                    return MEMORY_ERROR;
                }
                res = tmp;
            }
            strcat(res, romanTable[i].symbol);
            num -= romanTable[i].value;
        }
    }

    *out = res;
    return SUCCESS;
}

OperationStatus zeckendorf(unsigned int n, char **out) {
    if (!out) {
        return FAIL;
    }

    if (!n) {
        *out = malloc(2);
        if (!*out) {
            return MEMORY_ERROR;
        }

        strcpy(*out, "1");
        return SUCCESS;
    }

    int capacity = 2;
    unsigned int *fib = malloc(sizeof(unsigned int) * capacity);
    if (!fib) return MEMORY_ERROR;

    fib[0] = 1;
    fib[1] = 2;
    int count = 2;

    while (1) {
        unsigned int fnext = fib[count - 1] + fib[count - 2];
        if (fnext > n) break;
        if (count + 1 >= capacity) {
            capacity *= 2;
            unsigned int *tmp = realloc(fib, sizeof(unsigned int) * capacity);
            if (!tmp) { free(fib); return MEMORY_ERROR; }
            fib = tmp;
        }

        fib[count++] = fnext;
    }

    int *cf = calloc(count, sizeof(int));
    if (!cf) {
        free(fib); 
        return MEMORY_ERROR; 
    }

    for (int i = count - 1; i >= 0; i--) {
        if (fib[i] <= n) {
            n -= fib[i];
            cf[i] = 1;
        }
    }

    char *res = malloc(count + 2);
    if (!res) { 
        free(fib); 
        free(cf); 
        return MEMORY_ERROR; 
    }

    for (int i = 0; i < count; i++) {
        res[i] = cf[i] ? '1' : '0';
    }

    res[count] = '1';
    res[count + 1] = '\0';

    free(fib);
    free(cf);
    *out = res;
    return SUCCESS;
}

OperationStatus intToBase(int num, int base, char reg, char **res) {
    if (base < 2 || base > 36) {
        base = 10;
    }

    if (!num) {
        *res = malloc(2);
        if (!*res) {
            return MEMORY_ERROR;
        }

        (*res)[0] = '0';
        (*res)[1] = '\0';
        return SUCCESS;
    }

    int x = num;
    int capacity = 2;
    *res = malloc(capacity);
    if (!*res) {
        return MEMORY_ERROR;
    }

    int i = 0;
    for (; x; i++) {
        if (i + 1 >= capacity) {
            capacity *= 2;
            char *temp = realloc(*res, capacity);
            if (!temp) {
                free(*res);
                return MEMORY_ERROR;
            }

            *res = temp;
        }

        int digit = x % base;
        if (digit < 10) {
            (*res)[i] = '0' + digit;
        } else {
            if (reg == 'V') {
                (*res)[i] = 'A' + (digit - 10);
            } else {
                (*res)[i] = 'a' + (digit - 10);
            }
        }

        x /= base;
    }

    (*res)[i] = '\0';

    for (int j = 0; j < i / 2; j++) {
        char temp = (*res)[i - j - 1];
        (*res)[i - j - 1] = (*res)[j];
        (*res)[j] = temp;
    }

    return SUCCESS;
}

OperationStatus baseTo10(const char *num, int base, char reg, char **res) {
    if (base < 2 || base > 36) {
        base = 10;
    }

    if (!num || !res) {
        return FAIL;
    }

    const char *ptr = num;
    for (; *ptr; ptr++) {
        char c = *ptr;
        int valid = 0;

        if (isalpha(c)) {
            if (isupper(reg) && !isupper(c)) {
                return INVALID_NUMBER;
            }

            if (islower(reg) && !islower(c)) {
                return INVALID_NUMBER;
            }
        }

        char lwr = tolower(c);
        if (isdigit(lwr)) {
            valid = (lwr - '0') < base;
        } else if (isalpha(lwr)) {
            valid = (lwr - 'a' + 10) < base;
        }

        if (!valid) {
            return INVALID_NUMBER;
        }
    }

    char *endptr;
    long val = strtol(num, &endptr, base);
    if (*endptr != '\0') {
        return FAIL;
    }

    int len = snprintf(NULL, 0, "%ld", val);
    *res = malloc(len + 1);
    if (!*res) {
        return MEMORY_ERROR;
    }

    sprintf(*res, "%ld", val);
    return SUCCESS;
}

OperationStatus dumpBytes(const unsigned char *bytes, size_t size, char **res) {
    if (!bytes || !res) {
        return FAIL;
    }

    size_t capacity = size * (8 + 1) + 1;
    *res = malloc(capacity);
    if (!*res) {
        return MEMORY_ERROR;
    }

    (*res)[0] = '\0';
    char temp[9];
    for (size_t i = 0; i < size; i++) {
        unsigned char b = bytes[i];
        for (int bit = 7; bit >= 0; bit--) {
            temp[7 - bit] = (b & (1 << bit)) ? '1' : '0';
        }

        temp[8] = '\0';
        strcat(*res, temp);
        if (i != size - 1) {
            strcat(*res, " ");
        }
    }

    return SUCCESS;
}

static int voverfprintf(FILE *stream, char *out, const char *fmt, va_list args) {
    char tmpfmt[256];
    char tmpbuf[1024];
    size_t pos = 0;
    va_list copy;
    va_copy(copy, args);

    for (size_t i = 0; fmt[i]; ) {
        if (fmt[i] != '%') {
            if (stream) {
                fputc(fmt[i], stream);
            } else {
                out[pos++] = fmt[i];
            }

            i++;
            continue;
        }

        if (fmt[i + 1] == '%') {
            if (stream) {
                fputc('%', stream);
            } else {
                out[pos++] = '%';
            }

            i += 2;
            continue;
        }

        if (fmt[i + 1] == 'R' && fmt[i + 2] == 'o') {
            int val = va_arg(copy, int);
            char *res = NULL;
            OperationStatus os_torome = intToRome(val, &res);
            if (os_torome != SUCCESS) {
                fprintf(stderr, "ERROR\n");
            }

            if (res) {
                if (stream) {
                    fputs(res, stream);
                } else {
                    pos += sprintf(out + pos, "%s", res);
                }

                free(res);
            }
            
            i += 3;
            continue;
        }

        if (fmt[i + 1] == 'Z' && fmt[i + 2] == 'r') {
            unsigned int val = va_arg(copy, unsigned int);
            char *res = NULL;
            OperationStatus os_zeck = zeckendorf(val, &res);
            if (os_zeck != SUCCESS) {
                fprintf(stderr, "ERROR\n");
            }

            if (res) {
                if (stream) {
                    fputs(res, stream);
                } else {
                    pos += sprintf(out + pos, "%s", res);
                }

                free(res);
            }

            i += 3;
            continue;
        }

        if (fmt[i + 1] == 'C' && (fmt[i + 2] == 'v' || fmt[i + 2] == 'V')) {
            int num = va_arg(copy, int);
            int base = va_arg(copy, int);
            char *res = NULL;
            OperationStatus os_tobase = intToBase(num, base, fmt[i + 2], &res);
            if (os_tobase != SUCCESS) {
                fprintf(stderr, "ERROR\n");
                return 1;
            }
            if (res) {
                if (stream) {
                    fputs(res, stream);
                } else {
                    pos += sprintf(out + pos, "%s", res);
                }

                free(res);
            }
            i += 3;
            continue;
        }

        if ((fmt[i + 1] == 't' && fmt[i + 2] == 'o') || (fmt[i + 1] == 'T' && fmt[i + 2] == 'O')) {
            const char *num = va_arg(copy, const char*);
            int base = va_arg(copy, int);
            char *res = NULL;
            OperationStatus os_to10 = baseTo10(num, base, fmt[i + 2], &res);
            if (os_to10 != SUCCESS) {
                fprintf(stderr, "ERROR\n");
                return 1;
            }

            if (res) {
                if (stream) {
                    fputs(res, stream);
                } else {
                    pos += sprintf(out + pos, "%s", res);
                }

                free(res);
            }
            i += 3;
            continue;
        }

        if (fmt[i + 1] == 'm') {
            char type = fmt[i + 2];
            char *res = NULL;
            OperationStatus os_dump;
            switch (type) {
                case 'i': {
                    int v = va_arg(copy, int);
                    os_dump = dumpBytes((const unsigned char*)&v, sizeof(v), &res);
                    break;
                }
                case 'u': {
                    unsigned int v = va_arg(copy, unsigned int);
                    os_dump = dumpBytes((const unsigned char*)&v, sizeof(v), &res);
                    break;
                }
                case 'f': {
                    float v = (float)va_arg(copy, double);
                    os_dump = dumpBytes((const unsigned char*)&v, sizeof(v), &res);
                    break;
                }
                case 'd': {
                    double v = va_arg(copy, double);
                    os_dump = dumpBytes((const unsigned char*)&v, sizeof(v), &res);
                    break;
                }
                default: {
                    i++;
                    continue;
                }
            }

            if (os_dump != SUCCESS) {
                fprintf(stderr, "ERROR\n");
            }
            
            if (res) {
                if (stream) {
                    fputs(res, stream);
                } else {
                    pos += sprintf(out + pos, "%s", res);
                }

                free(res);
            }

            i += 3;
            continue;
        }

        const char *start = fmt + i;
        const char *next = strchr(start + 1, '%');
        size_t len = next ? (size_t)(next - start) : strlen(start);
        if (len >= sizeof(tmpfmt)) {
            len = sizeof(tmpfmt) - 1;
        }

        strncpy(tmpfmt, start, len);
        tmpfmt[len] = '\0';
        vsnprintf(tmpbuf, sizeof(tmpbuf), tmpfmt, copy);

        if (stream) {
            fputs(tmpbuf, stream);
        } else {
            pos += sprintf(out + pos, "%s", tmpbuf);
        }

        i += len;
    }

    if (!stream && out) {
        out[pos] = '\0';
    }

    va_end(copy);
    return (int)pos;
}

int overfprintf(FILE *stream, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    int r = voverfprintf(stream, NULL, fmt, args);
    va_end(args);
    return r;
}

int oversprintf(char *out, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    int r = voverfprintf(NULL, out, fmt, args);
    va_end(args);
    return r;
}
