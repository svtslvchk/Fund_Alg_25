#include <stdio.h>
#include <stdlib.h>
#include "check_brackets.h"

char getReverseBracket(const char s) {
    if (s == ')') {
        return '(';
    }

    if (s == '}') {
        return '{';
    }

    if (s == ']') {
        return '[';
    }

    if (s == '>') {
        return '<';
    }

    return '\0';
}

int checkBrackets(const char *str) {
    int size = 0;
    int capacity = 2;
    char *brackets = malloc(capacity);
    if (!brackets) {
        fprintf(stderr, "Memory allocation error\n");
        return 0;
    }

    while (*str) {
        char c = *str;
        if (c == ')' || c == '}' || c == ']' || c == '>') {
            if (!size) {
                free(brackets);
                return 0;
            }
            char reverse_bracket = getReverseBracket(c);
            if (reverse_bracket != brackets[size - 1]) {
                free(brackets);
                return 0;
            }

            size--;
        } else if (c == '(' || c == '{' || c == '[' || c == '<') {
            if (size >= capacity) {
                capacity *= 2;
                char *temp = realloc(brackets, capacity);
                if (!temp) {
                    free(brackets);
                    fprintf(stderr, "Memory allocation error\n");
                    return 0;
                }

                brackets = temp;
            }

            brackets[size] = c;
            size++;
        }

        str++;
    }

    free(brackets);
    return size == 0;
}
