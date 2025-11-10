#define VECTOR_TYPE int
#include "vector.h"
#include <stdio.h>
#include <assert.h>

int CopyInt(int value) {
    return value;
}

void DeleteInt(int value) {
    (void)value;
}

void test_int_basic() {
    printf("Test 1: int vector basic operations... ");
    
    Vector v = create_vector(5, CopyInt, DeleteInt);
    assert(v.capacity == 5);
    assert(v.size == 0);
    
    push_back_vector(&v, 10);
    push_back_vector(&v, 20);
    push_back_vector(&v, 30);
    
    assert(v.size == 3);
    assert(get_at_vector(&v, 0) == 10);
    assert(get_at_vector(&v, 1) == 20);
    assert(get_at_vector(&v, 2) == 30);
    
    // Очистка стекового вектора
    erase_vector(&v);
    printf("PASSED\n");
}

void test_int_copy() {
    printf("Test 2: int vector copy... ");
    
    Vector v1 = create_vector(3, CopyInt, DeleteInt);
    push_back_vector(&v1, 100);
    push_back_vector(&v1, 200);
    
    Vector v2 = create_vector(1, CopyInt, DeleteInt);
    copy_vector(&v2, &v1);
    
    assert(v2.size == 2);
    assert(is_equal_vector(&v1, &v2));
    
    // Очистка стековых векторов
    erase_vector(&v1);
    erase_vector(&v2);
    printf("PASSED\n");
}

void test_int_heap_copy() {
    printf("Test 3: int vector heap copy... ");
    
    Vector v1 = create_vector(3, CopyInt, DeleteInt);
    push_back_vector(&v1, 5);
    push_back_vector(&v1, 15);
    
    Vector* v2 = copy_vector_new(&v1);
    assert(v2 != NULL);
    assert(v2->size == 2);
    assert(is_equal_vector(&v1, v2));
    
    // Очистка
    erase_vector(&v1);    // стековый
    delete_vector(v2);    // кучовый
    
    printf("PASSED\n");
}

void test_int_delete_at() {
    printf("Test 4: int vector delete at... ");
    
    Vector v = create_vector(5, CopyInt, DeleteInt);
    push_back_vector(&v, 10);
    push_back_vector(&v, 20);
    push_back_vector(&v, 30);
    push_back_vector(&v, 40);
    
    delete_at_vector(&v, 1); // Удаляем 20
    
    assert(v.size == 3);
    assert(get_at_vector(&v, 0) == 10);
    assert(get_at_vector(&v, 1) == 30);
    assert(get_at_vector(&v, 2) == 40);
    
    erase_vector(&v);
    printf("PASSED\n");
}

int main() {
    printf("=== Running Integer Vector Tests ===\n\n");
    
    test_int_basic();
    test_int_copy();
    test_int_heap_copy();
    test_int_delete_at();
    
    printf("\n=== All Integer Tests PASSED! ===\n");
    return 0;
}