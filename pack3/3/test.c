#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "liver.h"

void test_create_delete() {
    printf("Test 1: Create and delete liver... ");
    
    Date date = {15, 5, 1990};
    Liver* liver = createLiver(1, "Smith", "John", "Michael", date, 'M', 2500.50);
    
    assert(liver != NULL);
    assert(liver->id == 1);
    assert(strcmp(liver->surname, "Smith") == 0);
    assert(strcmp(liver->name, "John") == 0);
    
    deleteLiver(liver);
    printf("PASSED\n");
}

void test_validation() {
    printf("Test 2: Validation... ");
    
    Date date = {15, 5, 1990};
    
    // Невалидная фамилия
    Liver* invalid1 = createLiver(1, "Smith123", "John", "", date, 'M', 1000);
    assert(invalid1 == NULL);
    
    // Невалидный пол
    Liver* invalid2 = createLiver(1, "Smith", "John", "", date, 'X', 1000);
    assert(invalid2 == NULL);
    
    printf("PASSED\n");
}

void test_copy() {
    printf("Test 3: Copy liver... ");
    
    Date date = {15, 5, 1990};
    Liver* original = createLiver(1, "Smith", "John", "Michael", date, 'M', 2500.50);
    Liver* copy = copyLiver(original);
    
    assert(copy != NULL);
    assert(copy != original);
    assert(copy->id == original->id);
    assert(strcmp(copy->surname, original->surname) == 0);
    
    deleteLiver(original);
    deleteLiver(copy);
    printf("PASSED\n");
}

void test_age_calculation() {
    printf("Test 4: Age calculation... ");
    
    Date date = {1, 1, 2000};
    Liver* liver = createLiver(1, "Test", "Age", "", date, 'M', 1000);
    
    int age = calcAge(liver);
    assert(age >= 20 && age <= 30); // Реалистичный возраст для 2000 года
    
    deleteLiver(liver);
    printf("PASSED\n");
}

int main() {
    printf("=== Testing Liver ===\n\n");
    
    test_create_delete();
    test_validation();
    test_copy();
    test_age_calculation();
    
    printf("\n=== All Tests PASSED! ===\n");
    return 0;
}