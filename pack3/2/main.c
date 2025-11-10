#define VECTOR_TYPE int
#include "vector.h"
#include <stdio.h>

int CopyInt(int value) {
    return value;
}

void DeleteInt(int value) {
    (void)value;
}

int main() {
    // Создаем векторы
    Vector v1 = create_vector(2, CopyInt, DeleteInt);
    Vector v2 = create_vector(4, CopyInt, DeleteInt);
    Vector *v3 = NULL;

    // Работа с v1
    for (int i = 2; i < 5; i++) {
        push_back_vector(&v1, i);
    }

    // Копируем v1 в v2
    copy_vector(&v2, &v1);

    // Создаем копию в куче
    v3 = copy_vector_new(&v1);

    // Проверяем что все работает
    printf("v1 size: %zu\n", v1.size);
    printf("v2 size: %zu\n", v2.size);
    printf("v3 size: %zu\n", v3->size);
    
    printf("v1 == v2: %s\n", is_equal_vector(&v1, &v2) ? "YES" : "NO");
    printf("v1 == v3: %s\n", is_equal_vector(&v1, v3) ? "YES" : "NO");

    // Очистка
    erase_vector(&v1);
    erase_vector(&v2);
    delete_vector(v3);

    printf("Test completed!\n");
    return 0;
}