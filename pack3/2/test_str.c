#define VECTOR_TYPE char*
#include "vector.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

char* CopyString(char* str) {
    if (!str) return NULL;
    char* copy = malloc(strlen(str) + 1);
    if (copy) {
        strcpy(copy, str);
    }
    return copy;
}

void DeleteString(char* str) {
    free(str);
}

void test_str_basic() {
    printf("Test 1: string vector basic operations... ");
    
    Vector v = create_vector(3, CopyString, DeleteString);
    
    push_back_vector(&v, "hello");
    push_back_vector(&v, "world");
    push_back_vector(&v, "test");
    
    assert(v.size == 3);
    assert(strcmp(get_at_vector(&v, 0), "hello") == 0);
    assert(strcmp(get_at_vector(&v, 1), "world") == 0);
    assert(strcmp(get_at_vector(&v, 2), "test") == 0);
    
    erase_vector(&v);
    printf("PASSED\n");
}

void test_str_deep_copy() {
    printf("Test 2: string vector deep copy... ");
    
    Vector v1 = create_vector(2, CopyString, DeleteString);
    push_back_vector(&v1, "first");
    push_back_vector(&v1, "second");
    
    Vector v2 = create_vector(1, CopyString, DeleteString);
    copy_vector(&v2, &v1);
    
    assert(strcmp(get_at_vector(&v2, 0), "first") == 0);
    assert(strcmp(get_at_vector(&v2, 1), "second") == 0);
    
    erase_vector(&v1);
    erase_vector(&v2);
    printf("PASSED\n");
}

void test_str_heap_copy() {
    printf("Test 3: string vector heap copy... ");
    
    Vector v1 = create_vector(2, CopyString, DeleteString);
    push_back_vector(&v1, "apple");
    push_back_vector(&v1, "banana");
    
    Vector* v2 = copy_vector_new(&v1);
    assert(v2 != NULL);
    assert(strcmp(get_at_vector(v2, 0), "apple") == 0);
    assert(strcmp(get_at_vector(v2, 1), "banana") == 0);
    
    erase_vector(&v1);
    delete_vector(v2);
    printf("PASSED\n");
}

void test_str_delete_at() {
    printf("Test 4: string vector delete at... ");
    
    Vector v = create_vector(5, CopyString, DeleteString);
    push_back_vector(&v, "one");
    push_back_vector(&v, "two");
    push_back_vector(&v, "three");
    
    delete_at_vector(&v, 1);  
    
    assert(v.size == 2);
    assert(strcmp(get_at_vector(&v, 0), "one") == 0);
    assert(strcmp(get_at_vector(&v, 1), "three") == 0);
    
    erase_vector(&v);
    printf("PASSED\n");
}

int main() {
    printf("=== Running String Vector Tests ===\n\n");
    
    test_str_basic();
    test_str_deep_copy();
    test_str_heap_copy();
    test_str_delete_at();
    
    printf("\n=== All String Tests PASSED! ===\n");
    return 0;
}