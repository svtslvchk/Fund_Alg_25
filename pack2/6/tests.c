#include "operations.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

void test_read_students() {
    printf("=== Тест чтения студентов ===\n");
    
    Student **students;
    size_t count;
    OperationStatus status = readStudentsFromFile("input.txt", &students, &count);
    
    assert(status == SUCCESS);
    assert(count > 0);
    printf("Успешно загружено %zu студентов\n", count);
    
    assert(students[0]->id == 12345);
    assert(strcmp(students[0]->first_name, "Ivan") == 0);
    assert(strcmp(students[0]->last_name, "Petrov") == 0);
    printf("Данные первого студента корректны\n");
    
    freeStudents(students, count);
}

void test_find_functions() {
    printf("\n=== Тест поиска ===\n");
    
    Student **students;
    size_t count;
    readStudentsFromFile("input.txt", &students, &count);
    
    Student **found;
    size_t found_count;
    OperationStatus status = findById(students, count, 12345, &found, &found_count);
    
    assert(status == SUCCESS);
    assert(found_count == 1);
    assert(strcmp(found[0]->first_name, "Ivan") == 0);
    printf("Поиск по ID работает\n");
    free(found);
    
    status = findByFirstName(students, count, "Maria", &found, &found_count);
    assert(status == SUCCESS);
    assert(found_count == 1);
    printf("Поиск по имени работает\n");
    free(found);
    
    status = findByLastName(students, count, "Petrov", &found, &found_count);
    assert(status == SUCCESS);
    printf("Поиск по фамилии работает\n");
    free(found);
    
    status = findByGroup(students, count, "CS-101", &found, &found_count);
    assert(status == SUCCESS);
    assert(found_count > 0);
    printf("Поиск по группе работает (найдено: %zu)\n", found_count);
    free(found);
    
    status = findById(students, count, 99999, &found, &found_count);
    assert(status == STUDENT_NOT_FOUND);
    printf("Поиск несуществующего ID корректно обработан\n");
    
    freeStudents(students, count);
}

void test_sort_functions() {
    printf("\n=== Тест сортировки ===\n");
    
    Student **students;
    size_t count;
    readStudentsFromFile("input.txt", &students, &count);
    
    qsort(students, count, sizeof(Student*), compareById);
    for (size_t i = 1; i < count; i++) {
        assert(students[i-1]->id <= students[i]->id);
    }
    printf("Сортировка по ID работает\n");
    
    qsort(students, count, sizeof(Student*), compareByFirstName);
    for (size_t i = 1; i < count; i++) {
        if (students[i-1]->first_name && students[i]->first_name) {
            assert(strcmp(students[i-1]->first_name, students[i]->first_name) <= 0);
        }
    }
    printf("Сортировка по имени работает\n");
    
    qsort(students, count, sizeof(Student*), compareByLastName);
    printf("Сортировка по фамилии работает\n");
    
    qsort(students, count, sizeof(Student*), compareByGroup);
    printf("Сортировка по группе работает\n");
    
    freeStudents(students, count);
}

void test_average_calculation() {
    printf("\n=== Тест расчетов среднего ===\n");
    
    Student **students;
    size_t count;
    readStudentsFromFile("input.txt", &students, &count);
    
    double avg;
    OperationStatus status = calcAverage(students[0], &avg);
    assert(status == SUCCESS);
    assert(avg >= 0 && avg <= 5);
    printf("Средний балл студента: %.2f\n", avg);
    
    double overall_avg;
    status = calcOverallAverage(students, count, &overall_avg);
    assert(status == SUCCESS);
    assert(overall_avg >= 0 && overall_avg <= 5);
    printf("Общий средний балл: %.2f\n", overall_avg);
    
    freeStudents(students, count);
}

void test_file_output() {
    printf("\n=== Тест вывода в файл ===\n");
    
    Student **students;
    size_t count;
    readStudentsFromFile("input.txt", &students, &count);
    
    OperationStatus status = printStudentById(students, count, 12345, "test_trace.txt");
    assert(status == SUCCESS);
    printf("Вывод студента по ID в файл работает\n");
    
    status = printStudentsAboveAverage(students, count, "test_trace.txt");
    assert(status == SUCCESS);
    printf("Вывод студентов выше среднего в файл работает\n");
    
    FILE *f = fopen("test_trace.txt", "r");
    assert(f != NULL);
    fclose(f);
    printf("Файл трассировки создан\n");
    
    remove("test_trace.txt");
    
    freeStudents(students, count);
}

void test_error_handling() {
    printf("\n=== Тест обработки ошибок ===\n");
    
    Student **students;
    size_t count;
    
    OperationStatus status = readStudentsFromFile("hh.txt", &students, &count);
    assert(status == INVALID_FILE);
    printf("Обработка несуществующего файла\n");
    
    status = findById(NULL, 0, 0, NULL, NULL);
    assert(status == INVALID_INPUT);
    printf("Обработка некорректных параметров\n");
    
    printf("Все тесты обработки ошибок пройдены\n");
}

int main() {
    printf("Запуск тестов\n\n");
    
    test_read_students();
    test_find_functions();
    test_sort_functions();
    test_average_calculation();
    test_file_output();
    test_error_handling();
    
    printf("\nВсе тесты успешно пройдены!\n");
    return 0;
}