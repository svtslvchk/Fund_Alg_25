#include "operations.h"
#include <stdio.h>
#include <string.h>

int main() {
    printf("Enter epsilon:\n");
    float epsilon;
    scanf("%f", &epsilon);
    
    printf("Enter const name (pi, e, ln2, sqrt2, gamma):\n");    
    char name[20];
    scanf("%19s", name);

    if (strcmp(name, "pi") == 0) {
        calcConstAndPrint("pi", piLimit, piSeries, piEquation, epsilon);
    } else if (strcmp(name, "e") == 0) {
        calcConstAndPrint("e", eLimit, eSeries, eEquation, epsilon);
    } else if (strcmp(name, "ln2") == 0) {
        calcConstAndPrint("ln2", ln2Limit, ln2Series, ln2Equation, epsilon);
    } else if (strcmp(name, "sqrt2") == 0) {
        calcConstAndPrint("sqrt2", sqrt2Limit, sqrt2Composition, sqrt2Equation, epsilon);
    } else if (strcmp(name, "gamma") == 0) {
        calcConstAndPrint("gamma", gammaLimit, gammaSeries, gammaEquation, epsilon);
    } else {
        fprintf(stderr, "Unknown constant: %s\n", name);
    }

    return 0;
}