#include "check_brackets.h"
#include <stdio.h>

#define MAX_SIZE 1000

int main() {
    char str[MAX_SIZE];
    printf("Enter string: ");
    scanf("%999s", str);

    if (checkBrackets(str)) {
        printf("The brackets are placed correctly\n");
    } else {
        printf("The brackets are placed incorrectly\n");
    }

    return 0;
}