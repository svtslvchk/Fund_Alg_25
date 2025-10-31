#include "operations.h"
#include <stdio.h>

void *memchr(const void *str, int c, size_t n) {
    const unsigned char *s = str;
    for (size_t i = 0; i < n; i++) {
        if (s[i] == (unsigned char)c) {
            return (void *)(s + i);
        }
    }

    return NULL;
}
int memcmp(const void *str1, const void *str2, size_t n) {
    const unsigned char *s1 = str1;
    const unsigned char *s2 = str2;
    for (size_t i = 0; i < n; i++) {
        if (s1[i] != s2[i]) {
            return s1[i] - s2[i];
        }
    }

    return 0;
}

void *memcpy(void *dest, const void *src, size_t n) {
    const unsigned char *s = src;
    unsigned char *d = dest;
    for (size_t i = 0; i < n; i++) {
        d[i] = s[i];
    }

    return dest;
}

void *memset(void *str, int c, size_t n) {
    unsigned char *s = str;
    for (size_t i = 0; i < n; i++) {
        s[i] = (unsigned char)c;
    }

    return str;
}

char *strncat(char *dest, const char *src, size_t n) {
    size_t i = 0, j = 0;
    while (dest[i]) {
        i++;
    }

    for (j = 0; j < n && src[j] != '\0'; j++) {
        dest[i + j] = src[j];
    }

    dest[i + j] = '\0';
    return dest;
}

char *strchr(const char *str, int c) {
    while (*str) {
        if (*str == (unsigned char)c) {
            return (char *)str;
        }

        str++;
    }

    if (c == '\0') {
        return (char *)str;
    } else {
        return NULL;
    }
}

int strncmp(const char *str1, const char *str2, size_t n) {
    for (size_t i = 0; i < n; i++) {
        unsigned char s1 = str1[i];
        unsigned char s2 = str2[i];
        if (s1 != s2 || s1 == '\0' || s2 == '\0') {
            return s1 - s2;
        }
    }

    return 0;
}

char *strncpy(char *dest, const char *src, size_t n) {
    size_t i = 0;
    for (; i < n && src[i]; i++) {
        dest[i] = src[i];
    }

    for (; i < n; i++) {
        dest[i] = '\0';
    }

    return dest;
}

size_t strcspn(const char *str1, const char *str2) {
    size_t count = 0;
    for (size_t i = 0; str1[i] != '\0'; i++) {
        for (size_t j = 0 ; str2[j] != '\0'; j++) {
            if (str1[i] == str2[j]) {
                return count;
            }
        }

        count++;
    }

    return count;
}

size_t strlen(const char *str) {
    size_t count = 0;
    while (*str) {
        str++;
        count++;
    }

    return count;
}

char *strpbrk(const char *str1, const char *str2) {
    for (size_t i = 0; str1[i] != '\0'; i++) {
        for (size_t j = 0; str2[j] != '\0'; j++) {
            if (str1[i] == str2[j]) {
                return (char *)&str1[i];
            }
        }
    }

    return NULL;
}

char *strrchr(const char *str, int c) {
    char *last = NULL;
    while (*str) {
        if (*str == (char)c) {
            last = (char *)str;
        }

        str++;
    }

    return (char *)last;
}

char *strstr(const char *haystack, const char *needle) {
    if (!*needle) {
        return NULL;
    }

    while (*haystack) {
        const char *h = haystack;
        const char *n = needle;
        while (*h && *n && *h == *n) {
            h++;
            n++;
        }

        if (!*n) {
            return (char *)haystack;
        }

        haystack++;
    }

    return NULL;
}

char *strtok(char *str, const char *delim) {
    static char *s;
    if (str) {
        s = str;
    } else if (!s) {
        return NULL;
    }

    while (*s && strchr(delim, *s)) {
        s++;
    }

    if (!*s) {
        return NULL;
    }

    char *res = s;
    while (*s && !strchr(delim, *s)) {
        s++;
    }

    if (*s) {
        *s = '\0';
        s++;
    }

    return res;
}

#ifdef __linux__
static const char *ERRLIST[] = {
    "Success",                         
    "Operation not permitted",         
    "No such file or directory",       
    "No such process",                 
    "Interrupted system call",         
    "Input/output error",              
    "No such device or address",       
    "Argument list too long",          
    "Exec format error",               
    "Bad file descriptor",             
    "No child processes"               
};
#elif __APPLE__
static const char *ERRLIST[] = {
    "Undefined error: 0",              
    "Operation not permitted",         
    "No such file or directory",       
    "No such process",                 
    "Interrupted system call",         
    "Input/output error",              
    "Device not configured",           
    "Argument list too long",          
    "Exec format error",               
    "Bad file descriptor",             
    "No child processes"               
};
#endif

#define ERRLIST_SIZE (sizeof(ERRLIST) / sizeof(ERRLIST[0]))

char *strerror(int errnum) {
    static char buffer[128];

    if (errnum >= 0 && errnum < (int)ERRLIST_SIZE) {
        return (char *)ERRLIST[errnum];
    } else {
        #ifdef __linux__
        snprintf(buffer, sizeof(buffer), "Unknown error %d", errnum);
        #elif __APPLE__
        snprintf(buffer, sizeof(buffer), "Unknown error: %d", errnum);
        #else
        snprintf(buffer, sizeof(buffer), "Unknown system error %d", errnum);
        #endif
        return buffer;
    }
}