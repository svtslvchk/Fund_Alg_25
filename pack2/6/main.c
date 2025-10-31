#include "operations.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Использование: %s <файл_студентов> <трассировочный_файл>\n", argv[0]);
        printf("Пример: %s input.txt trace.txt\n", argv[0]);
        return 1;
    }

    const char *student_file = argv[1];
    const char *trace_file = argv[2];  

    printf("Файл студентов: %s\n", student_file);
    printf("Трассировочный файл: %s\n", trace_file);

    Student **students;
    size_t student_count;
    OperationStatus status = readStudentsFromFile(student_file, &students, &student_count);
    
    if (status != SUCCESS) {
        printf("Ошибка загрузки студентов: %s\n", getStatusMessage(status));
        return 1;
    }

    printf("Успешно загружено %zu студентов\n", student_count);

    int choice;
    do {
        printMenu();
        if (scanf("%d", &choice) != 1) {
            printf("Некорректный ввод\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        switch (choice) {
            case 1: { 
                size_t id;
                printf("Введите ID: ");
                if (scanf("%zu", &id) != 1) {
                    printf("Некорректный ID\n");
                    clearInputBuffer();
                    break;
                }
                
                Student **found;
                size_t found_count;
                status = findById(students, student_count, id, &found, &found_count);
                
                if (status == SUCCESS) {
                    printf("Найдено студентов: %zu\n", found_count);
                    for (size_t i = 0; i < found_count; i++) {
                        printf("- %s %s (ID: %zu, группа: %s)\n",
                               found[i]->first_name, found[i]->last_name,
                               found[i]->id, found[i]->group);
                    }
                    free(found);
                } else {
                    printf("Ошибка: %s\n", getStatusMessage(status));
                }
                break;
            }

            case 2: { 
                char name[100];
                printf("Введите имя: ");
                if (scanf("%99s", name) != 1) {
                    printf("Некорректное имя\n");
                    break;
                }
                
                Student **found;
                size_t found_count;
                status = findByFirstName(students, student_count, name, &found, &found_count);
                
                if (status == SUCCESS) {
                    printf("Найдено студентов: %zu\n", found_count);
                    for (size_t i = 0; i < found_count; i++) {
                        printf("- %s %s (ID: %zu, группа: %s)\n",
                               found[i]->first_name, found[i]->last_name,
                               found[i]->id, found[i]->group);
                    }
                    free(found);
                } else {
                    printf("Ошибка: %s\n", getStatusMessage(status));
                }
                break;
            }

            case 3: { 
                char last_name[100];
                printf("Введите фамилию: ");
                if (scanf("%99s", last_name) != 1) {
                    printf("Некорректная фамилия\n");
                    break;
                }
                
                Student **found;
                size_t found_count;
                status = findByLastName(students, student_count, last_name, &found, &found_count);
                
                if (status == SUCCESS) {
                    printf("Найдено студентов: %zu\n", found_count);
                    for (size_t i = 0; i < found_count; i++) {
                        printf("- %s %s (ID: %zu, группа: %s)\n",
                               found[i]->first_name, found[i]->last_name,
                               found[i]->id, found[i]->group);
                    }
                    free(found);
                } else {
                    printf("Ошибка: %s\n", getStatusMessage(status));
                }
                break;
            }

            case 4: { 
                char group[100];
                printf("Введите группу: ");
                if (scanf("%99s", group) != 1) {
                    printf("Некорректная группа\n");
                    break;
                }
                
                Student **found;
                size_t found_count;
                status = findByGroup(students, student_count, group, &found, &found_count);
                
                if (status == SUCCESS) {
                    printf("Найдено студентов: %zu\n", found_count);
                    for (size_t i = 0; i < found_count; i++) {
                        printf("- %s %s (ID: %zu, группа: %s)\n",
                               found[i]->first_name, found[i]->last_name,
                               found[i]->id, found[i]->group);
                    }
                    free(found);
                } else {
                    printf("Ошибка: %s\n", getStatusMessage(status));
                }
                break;
            }

            case 5: {
                qsort(students, student_count, sizeof(Student*), compareById);
                printf("Сортировка по ID завершена\n");
                printf("Результат сортировки:\n");
                printAllStudents(students, student_count);
                break;
            }

            case 6: { 
                qsort(students, student_count, sizeof(Student*), compareByFirstName);
                printf("Сортировка по имени завершена\n");
                printf("Результат сортировки:\n");
                printAllStudents(students, student_count);
                break;
            }

            case 7: { 
                qsort(students, student_count, sizeof(Student*), compareByLastName);
                printf("Сортировка по фамилии завершена\n");
                printf("Результат сортировки:\n");
                printAllStudents(students, student_count);
                break;
            }

            case 8: { 
                qsort(students, student_count, sizeof(Student*), compareByGroup);
                printf("Сортировка по группе завершена\n");
                printf("Результат сортировки:\n");
                printAllStudents(students, student_count);
                break;
            }

            case 9: { 
                size_t id;
                printf("Введите ID студента: ");
                if (scanf("%zu", &id) != 1) {
                    printf("Некорректный ID\n");
                    clearInputBuffer();
                    break;
                }
                
                status = printStudentById(students, student_count, id, trace_file);
                printf("Результат записан в файл %s: %s\n", trace_file, getStatusMessage(status));
                break;
            }

            case 10: { 
                status = printStudentsAboveAverage(students, student_count, trace_file);
                printf("Результат записан в файл %s: %s\n", trace_file, getStatusMessage(status));
                break;
            }

            case 0:
                printf("Выход...\n");
                break;

            default:
                printf("Неверный выбор. Попробуйте снова.\n");
        }
    } while (choice != 0);

    freeStudents(students, student_count);
    printf("Программа завершена. Проверьте трассировочный файл: %s\n", trace_file);
    
    return 0;
}