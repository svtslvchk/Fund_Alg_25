#include "operations.h"
#include <stdio.h>

OperationStatus romeToInt(const char *str, int *res) {
    if (!str || !res) {
        return FAIL;
    }

    RomanDigit table[] = {
        {1000,"M"}, {900,"CM"}, {500,"D"}, {400,"CD"},
        {100,"C"}, {90,"XC"}, {50,"L"}, {40,"XL"},
        {10,"X"}, {9,"IX"}, {5,"V"}, {4,"IV"}, {1,"I"}
    };

    *res = 0;
    while (*str) {
        int f = 0;
        for (int i = 0; i < 13; i++) {
            if (strncmp(str, table[i].symbol, strlen(table[i].symbol)) == 0) {
                *res += table[i].value;
                str += strlen(table[i].symbol);
                f = 1;
                break;
            }
        }

        if (!f) {
            return INVALID_NUMBER;
        }
    }

    return SUCCESS;

}

OperationStatus zeckendorfToInt(const char *str, unsigned int *res) {
    if (!str || !res) {
        return FAIL;
    }

    int len = strlen(str);
    if (len < 1) {
        return INVALID_NUMBER;
    }

    if (str[len - 1] != '1') {
        return INVALID_NUMBER;
    }

    if (str[0] == '1' && str[1] == '\0') {
        *res = 0;
        return SUCCESS;
    }

    *res = 0;
    unsigned int *fib = malloc(sizeof(unsigned int) * (len - 1));
    if (!fib) {
        return MEMORY_ERROR;
    }

    fib[0] = 1;
    fib[1] = 2;
    int count = 2;

    while (count < len - 1) {
        fib[count] = fib[count - 1] + fib[count - 2];
        count++;
    }

    for (int i = 0; i < count; i++) {
        if (str[i] == '1') {
            *res += fib[i];
        } else if (str[i] != '0') {
            free(fib);
            return INVALID_NUMBER;
        }
    }

    free(fib);
    return SUCCESS;
}

OperationStatus baseTo10(const char *num, int base, char reg, int *res) {
    if (!num || !res) {
        return FAIL;
    }

    if (base < 2 || base > 36) {
        base = 10;
    }

    *res = 0;
    while (*num) {
        int val = 0;
        if (isdigit(*num)) {
            val = *num - '0';
        } else if (isalpha(*num)) {
            if (reg == 'V') {
                if (*num >= 'a' && *num <= 'z') {
                    return INVALID_NUMBER;
                }

                val = *num - 'A' + 10;
            } else if (reg == 'v') {
                if (*num >= 'A' && *num <= 'Z') {
                    return INVALID_NUMBER;
                }

                val = *num - 'a' + 10;
            }
        } else {
            return FAIL;
        }

        *res = *res * base + val;
        num++;
    }

    return SUCCESS;
}

int overfscanf(FILE *stream, const char *format, ...) {
    va_list args;
    va_start(args, format);
    int count = 0;
    char token[256];

    while (*format) {
        if (*format != '%') {
            int c = fgetc(stream);
            if (c == EOF || c != *format) {
                if (c != EOF) {
                    ungetc(c, stream);
                }

                break;
            }

            format++;
            continue;
        }
// "%d hello %d" "12 hell 12"

        if (*(format + 1) == '%') {
            int c = fgetc(stream);
            if (c != '%') {
                if (c != EOF) {
                    ungetc(c, stream);
                }

                break;
            }
            format += 2;
            continue;
        }

        format++;

        if (*format == 'R' && *(format + 1) == 'o') {
            int *ptr = va_arg(args, int *);
            if (!fscanf(stream, "%s", token)) {
                break;
            }

            OperationStatus os_rome = romeToInt(token, ptr);
            if (os_rome == SUCCESS) {
                count++;
            } else {
                fprintf(stderr, "ERROR\n");
                return 1;
            }

            format += 2;
            continue;
        }

        if (*format == 'Z' && *(format + 1) == 'r') {
            unsigned int *ptr = va_arg(args, unsigned int *);
            if (!fscanf(stream, "%s", token)) {
                break;
            }

            OperationStatus os_zeck = zeckendorfToInt(token, ptr);
            if (os_zeck == SUCCESS) {
                count++;
            } else {
                fprintf(stderr, "ERROR\n");
                return 1;
            }

            format += 2;
            continue;
        }

        if (*format == 'C' && (*(format + 1) == 'V' || *(format + 1) == 'v')) {
            int *ptr = va_arg(args, int *);
            int base = va_arg(args, int);
            char reg = *(format + 1);

            if (!fscanf(stream, "%s", token)) {
                break;
            }

            OperationStatus os_to10 = baseTo10(token, base, reg, ptr);
            if (os_to10 == SUCCESS) {
                count++;
            } else {
                fprintf(stderr, "ERROR\n");
                return 1;
            }

            format += 2;
            continue;
        }

        {
            void *ptr = va_arg(args, void *);
            switch (*format) {
                case 'd': {
                    int val;
                    if (fscanf(stream, "%d", &val) == 1) {
                        *(int *)ptr = val;
                        count++;
                    }

                    break;
                }
                case 'u': {
                    unsigned int val;
                    if (fscanf(stream, "%u", &val) == 1) {
                        *(unsigned int *)ptr = val;
                        count++;
                    }

                    break;
                }
                case 'x': case 'X': {
                    unsigned int val;
                    if (fscanf(stream, "%x", &val) == 1) {
                        *(unsigned int *)ptr = val;
                        count++;
                    }

                    break;
                }
                case 'f': {
                    float val;
                    if (fscanf(stream, "%f", &val) == 1) {
                        *(float *)ptr = val;
                        count++;
                    }

                    break;
                }
                case 's': {
                    if (fscanf(stream, "%255s", token) == 1) {
                        strcpy((char *)ptr, token); 
                        count++;
                    }

                    break;
                }
                case 'c': {
                    char val;
                    if (fscanf(stream, " %c", &val) == 1) { 
                        *(char *)ptr = val;
                        count++;
                    }

                    break;
                }
                default:
                    va_end(args);
                    return count;
            }

            format++;
            continue;
        }
    }

    va_end(args);
    return count;
}

int oversscanf(char *str, const char *format, ...) {
    va_list args;
    va_start(args, format);
    const char *p = str;
    char token[256];
    int count = 0;

    while (*format) {
        if (*format != '%') {
            if (isspace((unsigned char)*format)) {
                while (isspace((unsigned char)*p)) {
                    p++;
                }

                format++;
                continue;
            }

            if (*p == '\0' || *p != *format) {
                break;
            }
            
            p++;
            format++;
            continue;
        }


        if (*(format + 1) == '%') {
            if (*p != '%') {
                break;
            }

            p++;
            format += 2;
            continue;
        }

        format++;

        if (*format == 'R' && *(format + 1) == 'o') {
            int *ptr = va_arg(args, int *);
            if (!sscanf(p, "%s", token)) {
                break;
            }

            OperationStatus os_rome = romeToInt(token, ptr);
            if (os_rome == SUCCESS) {
                count++;
            } else {
                fprintf(stderr, "ERROR\n");
                return 1;
            }

            p += strcspn(p, " \t\n");
            p += strspn(p, " \t\n");
            format += 2;
            continue;
        }

        if (*format == 'Z' && *(format + 1) == 'r') {
            unsigned int *ptr = va_arg(args, unsigned int *);
            if (!sscanf(p, "%s", token)) {
                break;
            }

            OperationStatus os_zeck = zeckendorfToInt(token, ptr);
            if (os_zeck == SUCCESS) {
                count++;
            } else {
                fprintf(stderr, "ERROR\n");
                return 1;
            }

            p += strcspn(p, " \t\n");
            p += strspn(p, " \t\n");
            format += 2;
            continue;
        }

        if (*format == 'C' && (*(format + 1) == 'V' || *(format + 1) == 'v')) {
            int *ptr = va_arg(args, int *);
            int base = va_arg(args, int);
            char reg = *(format + 1);
            if (!sscanf(p, "%s", token)) {
                break;
            }

            OperationStatus os_to10 = baseTo10(token, base, reg, ptr);
            if (os_to10 == SUCCESS) {
                count++;
            } else {
                fprintf(stderr, "ERROR\n");
                return 1;
            }

            p += strcspn(p, " \t\n");
            p += strspn(p, " \t\n");
            format += 2;
            continue;
        }

        {
            void *ptr = va_arg(args, void *);
            const char *start = p;
            char *endptr = NULL;

            switch (*format) {
                case 'd': { 
                    long val = strtol(p, &endptr, 10);
                    if (endptr == p) {
                        endptr = NULL;
                    } else {
                        *(int *)ptr = (int)val;
                    }

                    break;
                }
                case 'u': { 
                    unsigned long val = strtoul(p, &endptr, 10);
                    if (endptr == p) {
                        endptr = NULL;
                    } else {
                        *(unsigned int *)ptr = (unsigned int)val;
                    }

                    break;
                }
                case 'x': case 'X': { 
                    unsigned long val = strtoul(p, &endptr, 16);
                    if (endptr == p) {
                        endptr = NULL;
                    } else {
                        *(unsigned int *)ptr = (unsigned int)val;
                    }

                    break;
                }
                case 'f': { 
                    double val = strtod(p, &endptr);
                    if (endptr == p) {
                        endptr = NULL;
                    } else {
                        *(float *)ptr = (float)val;
                    }

                    break;
                }
                case 's': { 
                    if (sscanf(p, "%255s", token) == 1) {
                        strcpy((char *)ptr, token);
                        endptr = (char *)(p + strlen(token));
                    } else {
                        endptr = NULL;
                    }

                    break;
                }
                case 'c': { 
                    while (*p && isspace((unsigned char)*p)) p++;
                    if (*p) {
                        *(char *)ptr = *p;
                        endptr = (char *)(p + 1);
                    } else {
                        endptr = NULL;
                    }

                    break;
                }
                default:
                    va_end(args);
                    return count;
            }

            if (endptr && endptr != start) {
                p = endptr;
                p += strspn(p, " \t\n"); 
                count++;
            }

            format++;
            continue;
        }
    }

    va_end(args);
    return count;
}