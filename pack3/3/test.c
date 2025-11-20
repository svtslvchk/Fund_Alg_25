#include <stdio.h>
#include <assert.h>
#include <string.h>

// Определяем тип для списка - указатели на Liver
#include "liver.h"
#define LIST_TYPE Liver*
#include "linked_list.h"

// ==================== ТЕСТЫ ДЛЯ LIVER ====================

void test_liver_basic() {
    printf("Test 1: Liver creation and validation... ");
    
    Date date = {15, 5, 1990};
    Liver* liver = createLiver(1, "Smith", "John", "Michael", date, 'M', 2500.50);
    
    assert(liver != NULL);
    assert(liver->id == 1);
    assert(strcmp(liver->surname, "Smith") == 0);
    assert(strcmp(liver->name, "John") == 0);
    
    deleteLiver(liver);
    printf("PASSED\n");
}

void test_liver_validation() {
    printf("Test 2: Liver validation... ");
    
    Date date = {15, 5, 1990};
    
    // Невалидная фамилия
    Liver* invalid1 = createLiver(1, "Smith123", "John", "", date, 'M', 1000);
    assert(invalid1 == NULL);
    
    // Невалидный пол
    Liver* invalid2 = createLiver(1, "Smith", "John", "", date, 'X', 1000);
    assert(invalid2 == NULL);
    
    printf("PASSED\n");
}

void test_liver_copy() {
    printf("Test 3: Liver copy... ");
    
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

// ==================== ТЕСТЫ ДЛЯ СПИСКА ====================

void test_list_operations() {
    printf("Test 4: List basic operations... ");
    
    LinkedList list = create_list();
    Date date = {15, 5, 1990};
    
    Liver* liver1 = createLiver(1, "Smith", "John", "", date, 'M', 1000);
    Liver* liver2 = createLiver(2, "Johnson", "Jane", "", date, 'W', 2000);
    
    push_back_list(&list, liver1);
    push_back_list(&list, liver2);
    assert(list.size == 2);
    
    Liver* retrieved = get_at_list(&list, 0);
    assert(retrieved->id == 1);
    
    erase_list(&list);
    deleteLiver(liver1);
    deleteLiver(liver2);
    printf("PASSED\n");
}

// ==================== ТЕСТЫ ДЛЯ СТЕКА ====================

void test_stack_operations() {
    printf("Test 5: Stack operations... ");

    LinkedList stack = create_list();
    Date date = {15, 5, 1990};

    Liver* liver1 = createLiver(1, "Smith", "John", "", date, 'M', 1000);
    Liver* liver2 = createLiver(2, "Johnson", "Jane", "", date, 'W', 2000);

    push_stack(&stack, liver1);
    push_stack(&stack, liver2);
    assert(stack.size == 2);

    Liver* top = peek_stack(&stack);
    assert(top->id == 2);

    top = pop_stack(&stack);
    assert(top->id == 2);
    deleteLiver(top);    // удалили liver2 сразу после pop

    // теперь в списке остался только liver1
    erase_list(&stack);  // освобождает только узлы, не данные
    deleteLiver(liver1); // удаляем единственный оставшийся объект

    // НЕ вызывать deleteLiver(liver2) — он уже удалён выше
    printf("PASSED\n");
}

// ==================== ТЕСТЫ ДЛЯ ОЧЕРЕДИ ====================

void test_queue_operations() {
    printf("Test 6: Queue operations... ");

    LinkedList queue = create_list();
    Date date = {15, 5, 1990};

    Liver* liver1 = createLiver(1, "Smith", "John", "", date, 'M', 1000);
    Liver* liver2 = createLiver(2, "Johnson", "Jane", "", date, 'W', 2000);

    enqueue(&queue, liver1);
    enqueue(&queue, liver2);
    assert(queue.size == 2);

    Liver* front = peek_queue(&queue);
    assert(front->id == 1);

    front = dequeue(&queue);
    assert(front->id == 1);
    deleteLiver(front);  // удалили liver1

    // теперь в очереди остался только liver2
    erase_list(&queue);
    deleteLiver(liver2); // удаляем оставшийся объект

    // НЕ вызывать deleteLiver(liver1) — он уже удалён выше
    printf("PASSED\n");
}


// ==================== ОСНОВНАЯ ФУНКЦИЯ ====================

int main() {
    printf("=== COMPLETE TEST SUITE ===\n\n");
    
    test_liver_basic();
    test_liver_validation();
    test_liver_copy();
    test_list_operations();
    test_stack_operations();
    test_queue_operations();
    
    printf("\n=== ALL TESTS PASSED! ===\n");
    return 0;
}