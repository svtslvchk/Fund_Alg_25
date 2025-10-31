#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "operations.h"

void test_hasFiniteRepresentation() {
    bool res;
    OperationsStatus st;

    printf("=== Tests for hasFiniteRepresentation() ===\n");

    st = hasFiniteRepresentation(2, 0.5, &res);
    assert(st == SUCCESS && res == true);
    printf("Test 1 passed\n");

    st = hasFiniteRepresentation(2, 0.1, &res);
    assert(st == SUCCESS && res == true);
    printf("Test 2 passed\n");

    st = hasFiniteRepresentation(8, 0.25, &res);
    assert(st == SUCCESS && res == true);
    printf("Test 3 passed\n");

    st = hasFiniteRepresentation(10, 1.0 / 6.0, &res);
    assert(st == SUCCESS && res == false);
    printf("Test 4 passed\n");

    st = hasFiniteRepresentation(10, 1.2, &res);
    assert(st == INVALID_NUMBER);
    printf("Test 5 passed\n");

    st = hasFiniteRepresentation(1, 0.5, &res);
    assert(st == INVALID_BASE);
    printf("Test 6 passed\n");

    printf("All tests hasFiniteRepresentation() passed\n\n");
}

void test_checkFiniteRepresentation() {
    printf("=== Tests for checkFiniteRepresentation() ===\n");

    bool *results = NULL;
    OperationsStatus st = checkFiniteRepresentation(&results, 10, 5,
                                                    0.125, 0.4, 0.5, 1.0 / 3.0, 0.875);
    assert(st == SUCCESS);

    assert(results[0] == true);
    assert(results[1] == true);
    assert(results[2] == true);
    assert(results[3] == false);
    assert(results[4] == true);
    printf("Test 1 passed\n");

    free(results);
    results = NULL;

    st = checkFiniteRepresentation(&results, 10, 3, 0.5, -0.2, 0.25);
    assert(st == INVALID_NUMBER);
    printf("Test 2 passed\n");
    free(results);
    results = NULL;

    st = checkFiniteRepresentation(&results, 1, 2, 0.5, 0.25);
    assert(st == INVALID_BASE);
    printf("Test 3 passed\n");
    free(results);
    results = NULL;

    printf("All tests checkFiniteRepresentation() passed\n");
}


int main() {
    printf("Running tests...\n\n");
    test_hasFiniteRepresentation();
    test_checkFiniteRepresentation();
    printf("\nAll tests successfully passed!\n");
    return 0;
}
