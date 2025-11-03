#include "check_brackets.h"
#include <stdio.h>

#define MAX_SIZE 1000

int main() {
    char str[MAX_SIZE];
    printf("Enter string: ");
    fgets(str, MAX_SIZE, stdin);

    for (int i = 0; str[i]; i++) {
        if (str[i] == '\n') {
            str[i] = '\0';
            break;
        }
    }

    if (checkBrackets(str)) {
        printf("The brackets are placed correctly\n");
    } else {
        printf("The brackets are placed incorrectly\n");
    }

    return 0;
}