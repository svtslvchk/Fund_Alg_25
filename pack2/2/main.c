#include <stdio.h>
#include "operations.h"

int main() {
    printf("=== Demonstration of custom string/memory functions ===\n\n");

    char text[] = "Hello, world!";
    printf("Length of '%s' = %zu\n", text, strlen(text));

    char copy[50];
    strncpy(copy, text, 50);
    printf("Copied string: %s\n", copy);

    char cat[100] = "Hello";
    strncat(cat, ", bro!", 9);
    printf("Concatenated: %s\n", cat);

    const char *s = "banana";
    printf("First 'a' in '%s': %s\n", s, strchr(s, 'a'));
    printf("Last 'a' in '%s': %s\n", s, strrchr(s, 'a'));

    const char *phrase = "I love programming in C";
    printf("Substring 'program': %s\n", strstr(phrase, "program"));

    char csv[] = "one,two,three";
    printf("Tokens:\n");
    char *token = strtok(csv, ",");
    while (token) {
        printf("%s\n", token);
        token = strtok(NULL, ",");
    }

    printf("\nError 2 message: %s\n", strerror(2));
    printf("Error 999 message: %s\n", strerror(999));

    printf("\n=== End of demonstration ===\n");
    return 0;
}
