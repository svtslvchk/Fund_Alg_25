#include "operations.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void test_convertToBase() {
    printf("Testing convertToBase function...\n");
    
    char *result = NULL;

    printf("Test 1: Binary conversion... ");
    assert(convertToBase(5, 1, &result) == SUCCESS);
    assert(strcmp(result, "101") == 0);
    free(result);
    result = NULL;
    printf("PASS\n");

    printf("Test 2: Base 4 conversion... ");
    assert(convertToBase(13, 2, &result) == SUCCESS);
    assert(strcmp(result, "31") == 0);
    free(result);
    result = NULL;
    printf("PASS\n");

    printf("Test 3: Base 8 conversion... ");
    assert(convertToBase(26, 3, &result) == SUCCESS);
    assert(strcmp(result, "32") == 0);
    free(result);
    result = NULL;
    printf("PASS\n");

    printf("Test 4: Base 16 conversion... ");
    assert(convertToBase(255, 4, &result) == SUCCESS);
    assert(strcmp(result, "FF") == 0);
    free(result);
    result = NULL;
    printf("PASS\n");

    printf("Test 5: Base 32 conversion... ");
    assert(convertToBase(123, 5, &result) == SUCCESS);
    assert(strcmp(result, "3R") == 0);
    free(result);
    result = NULL;
    printf("PASS\n");
    
    printf("Test 6: Letter digits... ");
    assert(convertToBase(10, 4, &result) == SUCCESS);
    assert(strcmp(result, "A") == 0);
    free(result);
    result = NULL;
    printf("PASS\n");
    
    printf("Test 7: Number 0... ");
    OperationStatus status = convertToBase(0, 3, &result);
    printf("Status: %d, Result: %s... ", status, result ? result : "NULL");
    assert(status == SUCCESS);
    assert(strcmp(result, "0") == 0);
    free(result);
    result = NULL;
    printf("PASS\n");
    
    printf("Test 8: Number 1... ");
    assert(convertToBase(1, 3, &result) == SUCCESS);
    assert(strcmp(result, "1") == 0);
    free(result);
    result = NULL;
    printf("PASS\n");
    
    printf("Test 9: Large number... ");
    assert(convertToBase(1024, 4, &result) == SUCCESS);
    assert(strcmp(result, "400") == 0);
    free(result);
    result = NULL;
    printf("PASS\n");
    
    printf("Test 10: Invalid r error... ");
    assert(convertToBase(10, 6, &result) == INVALID_INPUT);
    assert(convertToBase(10, 0, &result) == INVALID_INPUT);
    printf("PASS\n");
    
    printf("Test 11: NULL result error... ");
    assert(convertToBase(10, 2, NULL) == INVALID_INPUT);
    printf("PASS\n");
    
    printf("All convertToBase tests passed! \n\n");
}

int main() {
    printf("=== Starting Unit Tests ===\n\n");
    
    test_convertToBase();
    
    printf("=== All Tests Completed Successfully ===\n");
    return 0;
}