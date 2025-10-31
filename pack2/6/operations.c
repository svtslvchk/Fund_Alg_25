#include "operations.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int isCorrectString(const char *s) {
    while (*s) {
        if (!isalpha(*s)) {
            return 0;
        }

        s++;
    }

    return 1;
}

OperationStatus readStudentsFromFile(const char *input_filename, Student ***students, size_t *count) {
    if (!input_filename || !students || !count) {
        return INVALID_INPUT;
    }

    FILE *f = fopen(input_filename, "r");  
    if (!f) {
        return INVALID_FILE;
    }

    *count = 0;
    size_t capacity = 2;
    *students = malloc(sizeof(Student *) * capacity);
    if (!*students) {
        fclose(f);
        return MEMORY_ERROR;
    }

    char line[256];
    while (fgets(line, sizeof(line), f)) {
        if (*count >= capacity) {
            capacity *= 2;
            Student **temp = realloc(*students, sizeof(Student *) * capacity);
            if (!temp) {
                OperationStatus os_free = freeStudents(*students, *count);
                fclose(f);
                return (os_free == SUCCESS) ? MEMORY_ERROR : os_free;
            }

            *students = temp;
        }

        Student *student = malloc(sizeof(Student));
        if (!student) {
            OperationStatus os_free = freeStudents(*students, *count);
            fclose(f);
            return (os_free == SUCCESS) ? MEMORY_ERROR : os_free;
        }

        char *token = strtok(line, " ");
        if (!token) {
            free(student);
            continue;  
        }
        student->id = atoi(token);

        token = strtok(NULL, " ");
        if (!token || !isCorrectString(token)) {
            free(student);
            continue;
        }
        student->first_name = malloc(strlen(token) + 1);
        if (!student->first_name) {
            free(student);
            OperationStatus os_free = freeStudents(*students, *count);
            fclose(f);
            return (os_free == SUCCESS) ? MEMORY_ERROR : os_free;
        }
        strcpy(student->first_name, token);

        token = strtok(NULL, " ");
        if (!token || !isCorrectString(token)) {
            free(student->first_name);
            free(student);
            continue;
        }
        student->last_name = malloc(strlen(token) + 1);
        if (!student->last_name) {
            free(student->first_name);
            free(student);
            OperationStatus os_free = freeStudents(*students, *count);
            fclose(f);
            return (os_free == SUCCESS) ? MEMORY_ERROR : os_free;
        }
        strcpy(student->last_name, token);

        token = strtok(NULL, " ");
        if (!token) {
            free(student->first_name);
            free(student->last_name);
            free(student);
            continue;
        }

        student->group = malloc(strlen(token) + 1);
        if (!student->group) {
            free(student->first_name);
            free(student->last_name);
            free(student);
            OperationStatus os_free = freeStudents(*students, *count);
            fclose(f);
            return (os_free == SUCCESS) ? MEMORY_ERROR : os_free;
        }

        strcpy(student->group, token);

        student->grades = malloc(sizeof(unsigned char) * GRADES_COUNT);
        if (!student->grades) {
            free(student->first_name);
            free(student->last_name);
            free(student->group);
            free(student);
            OperationStatus os_free = freeStudents(*students, *count);
            fclose(f);
            return (os_free == SUCCESS) ? MEMORY_ERROR : os_free;
        }

        int valid_grades = 1;
        for (int i = 0; i < GRADES_COUNT; i++) {
            token = strtok(NULL, " \n"); 
            if (!token) {
                valid_grades = 0;
                break;
            }

            int grade = atoi(token);
            if (grade < 0 || grade > 5) {
                valid_grades = 0;
                break;
            }

            student->grades[i] = (unsigned char)grade;
        }

        if (!valid_grades) {
            free(student->first_name);
            free(student->last_name);
            free(student->group);
            free(student->grades);
            free(student);
            continue;
        }

        (*students)[*count] = student;
        (*count)++;  
    }

    fclose(f);
    return (*count > 0) ? SUCCESS : STUDENT_NOT_FOUND;
}

OperationStatus freeStudents(Student **students, size_t count) {
    if (!students) {
        return INVALID_INPUT;
    }

    Student *student;
    for (size_t i = 0; i < count; i++) {
        student = students[i];
        if (student) {
            free(student->first_name);
            free(student->last_name);
            free(student->group);
            free(student->grades);
            free(student);
        }
    }

    free(students);
    return SUCCESS;
}

OperationStatus calcAverage(Student *student, double *average) {
    if (!student || !average || !student->grades) {
        return INVALID_INPUT;
    }

    *average = 0.0;
    unsigned char *scores = student->grades;
    for (int i = 0; i < GRADES_COUNT; i++) {
        *average += (double)scores[i];
    }

    *average /= GRADES_COUNT;
    return SUCCESS;
}

OperationStatus calcOverallAverage(Student **students, size_t count, double *overall_average) {
    if (!students || !overall_average) {
        return INVALID_INPUT;
    }

    *overall_average = 0.0;
    if (!count) {
        *overall_average = 0.0;
        return SUCCESS;
    }

    size_t valid = 0;
    for (size_t i = 0; i < count; i++) {
        if (!students[i]) {
            continue;
        }

        double average = 0.0;
        OperationStatus os_avrg = calcAverage(students[i], &average);
        if (os_avrg != SUCCESS) {
            return os_avrg;
        }

        *overall_average += average;
        valid++;
    }

    if (!valid) {
        *overall_average = 0.0;
        return SUCCESS;
    }

    *overall_average /= valid;
    return SUCCESS;
}

OperationStatus findById(Student **students, size_t count, const size_t id, Student ***found, size_t *found_count) {
    if (!students || !found || !found_count) {
        return INVALID_INPUT;
    }

    size_t capacity = 2;
    *found = malloc(sizeof(Student *) * capacity);
    if (!*found) {
        return MEMORY_ERROR;
    }

    *found_count = 0;
    for (size_t i = 0; i < count; i++) {
        if (*found_count >= capacity) {
            capacity *= 2;
            Student **temp = realloc(*found, sizeof(Student *) * capacity);
            if (!temp) {
                free(*found);
                return MEMORY_ERROR;
            }

            *found = temp;
        }

        if (students[i] && students[i]->id == id) {
            (*found)[*found_count] = students[i];
            (*found_count)++;
        }
    }

    if (!*found_count) {
        free(*found);
        *found = NULL;
        return STUDENT_NOT_FOUND;
    }

    return SUCCESS;
}

OperationStatus findByFirstName(Student **students, size_t count, const char *first_name, Student ***found, size_t *found_count) {
    if (!students || !first_name || !found || !found_count) {
        return INVALID_INPUT;
    }

    *found_count = 0;
    size_t capacity = 2;
    *found = malloc(sizeof(Student *) * capacity);
    if (!*found) {
        return MEMORY_ERROR;
    }

    for (size_t i = 0; i < count; i++) {
        if (*found_count >= capacity) {
            capacity *= 2;
            Student **temp = realloc(*found, sizeof(Student *) * capacity);
            if (!temp) {
                free(*found);
                return MEMORY_ERROR;
            }

            *found = temp;
        }

        if (students[i] && students[i]->first_name && strcmp(students[i]->first_name, first_name) == 0) {
            (*found)[*found_count] = students[i];
            (*found_count)++;
        }
    }

    if (!*found_count) {
        free(*found);
        *found = NULL;
        return STUDENT_NOT_FOUND;
    }

    return SUCCESS;
}


OperationStatus findByLastName(Student **students, size_t count, const char *last_name, Student ***found, size_t *found_count) {
    if (!students || !last_name || !found || !found_count) {
        return INVALID_INPUT;
    }

    *found_count = 0;
    size_t capacity = 2;
    *found = malloc(sizeof(Student *) * capacity);
    if (!*found) {
        return MEMORY_ERROR;
    }

    for (size_t i = 0; i < count; i++) {
        if (*found_count >= capacity) {
            capacity *= 2;
            Student **temp = realloc(*found, sizeof(Student *) * capacity);
            if (!temp) {
                free(*found);
                return MEMORY_ERROR;
            }

            *found = temp;
        }

        if (students[i] && students[i]->last_name && strcmp(students[i]->last_name, last_name) == 0) {
            (*found)[*found_count] = students[i];
            (*found_count)++;
        }
    }

    if (!*found_count) {
        free(*found);
        *found = NULL;
        return STUDENT_NOT_FOUND;
    }

    return SUCCESS;
}

OperationStatus findByGroup(Student **students, size_t count, const char *group, Student ***found, size_t *found_count) {
    if (!students || !group || !found || !found_count) {
        return INVALID_INPUT;
    }

    *found_count = 0;
    size_t capacity = 2;
    *found = malloc(sizeof(Student *) * capacity);
    if (!*found) {
        return MEMORY_ERROR;
    }

    for (size_t i = 0; i < count; i++) {
        if (*found_count >= capacity) {
            capacity *= 2;
            Student **temp = realloc(*found, sizeof(Student *) * capacity);
            if (!temp) {
                free(*found);
                return MEMORY_ERROR;
            }

            *found = temp;
        }

        if (students[i] && students[i]->group && strcmp(students[i]->group, group) == 0) {
            (*found)[*found_count] = students[i];
            (*found_count)++;
        }
    }

    if (!*found_count) {
        free(*found);
        *found = NULL;
        return STUDENT_NOT_FOUND;
    }

    return SUCCESS;
}

int compareById(const void *a, const void *b) {
    const Student *s1 = *(const Student **)a;
    const Student *s2 = *(const Student **)b;

    if (s1->id < s2->id) {
        return -1;
    }

    if (s1->id > s2->id) {
        return 1;
    }

    return 0;
}
int compareByFirstName(const void *a, const void *b) {
    const Student *s1 = *(const Student **)a;
    const Student *s2 = *(const Student **)b;

    if (!s1->first_name && !s2->first_name) {
        return 0;
    }

    if (!s1->first_name) {
        return -1;
    }

    if (!s2->first_name) {
        return 1;
    }

    return strcmp(s1->first_name, s2->first_name);
}
int compareByLastName(const void *a, const void *b) {
    const Student *s1 = *(const Student **)a;
    const Student *s2 = *(const Student **)b;

    if (!s1->last_name && !s2->last_name) {
        return 0;
    }

    if (!s1->last_name) {
        return -1;
    }

    if (!s2->last_name) {
        return 1;
    }

    return strcmp(s1->last_name, s2->last_name);
}
int compareByGroup(const void *a, const void *b) {
    const Student *s1 = *(const Student **)a;
    const Student *s2 = *(const Student **)b;

    if (!s1->group && !s2->group) {
        return 0;
    }

    if (!s1->group) {
        return -1;
    }

    if (!s2->group) {
        return 1;
    }

    return strcmp(s1->group, s2->group);
}

OperationStatus printStudentById(Student **students, size_t count, size_t id, const char *trace_filename) {
    if (!students || !trace_filename) {
        return INVALID_INPUT;
    }

    FILE *f = fopen(trace_filename, "a");
    if (!f) {
        return INVALID_FILE;
    }

    Student **found;
    size_t found_count;
    OperationStatus os_find = findById(students, count, id, &found, &found_count);
    if (os_find == SUCCESS) {
        Student *student = found[0];
        fprintf(f, "Данные студента\n");
        fprintf(f, "ID: %zu\n", student->id);
        fprintf(f, "ФИО: %s %s\n", student->last_name, student->first_name);
        fprintf(f, "Группа: %s\n", student->group);
        double avg;
        OperationStatus os_avg = calcAverage(student, &avg);
        if (os_avg == SUCCESS) {
            fprintf(f, "Средний балл: %g", avg);
        }

        free(found);
    } else {
        fprintf(f, "Студент с ID %zu не найден\n", id);
    }

    fclose(f);
    return SUCCESS;
}

OperationStatus printStudentsAboveAverage(Student **students, size_t count, const char *trace_filename) {
    if (!students || !trace_filename) {
        return INVALID_INPUT;
    }

    FILE *f = fopen(trace_filename, "a");
    if (!f) {
        return INVALID_FILE;
    }

    double overall_avg;
    OperationStatus os_ov_avg = calcOverallAverage(students, count, &overall_avg);
    if (os_ov_avg != SUCCESS) {
        return os_ov_avg;
    }

    fprintf(f, "Студенты с баллом, выше среднего (%g)\n", overall_avg);
    int found_count = 0;
    for (size_t i = 0; i < count; i++) {
        if (!students[i]) {
            continue;
        }
        double avg;
        OperationStatus os_avg = calcAverage(students[i], &avg);
        if (os_avg != SUCCESS) {
            return os_avg;
        }

        if (avg > overall_avg) {
            found_count++;
            fprintf(f, "%d) %s %s, %s, avg: %g\n", found_count, students[i]->last_name, students[i]->first_name, students[i]->group, avg);
        }
        
    }

    if (!found_count) {
        fprintf(f, "Студентов с баллом выше среднего не найдено\n");
    }

    fclose(f);
    return SUCCESS;
}

void printMenu() {
    printf("\n=== Меню управления студентами ===\n");
    printf("1. Поиск по ID\n");
    printf("2. Поиск по имени\n");
    printf("3. Поиск по фамилии\n");
    printf("4. Поиск по группе\n");
    printf("5. Сортировка по ID\n");
    printf("6. Сортировка по имени\n");
    printf("7. Сортировка по фамилии\n");
    printf("8. Сортировка по группе\n");
    printf("9. Вывести данные студента по ID в файл\n");
    printf("10. Вывести студентов с баллом выше среднего в файл\n");
    printf("0. Выход\n");
    printf("Выберите опцию: ");
}

const char* getStatusMessage(OperationStatus status) {
    switch (status) {
        case SUCCESS: return "Успешно";
        case INVALID_INPUT: return "Ошибка: некорректный ввод";
        case INVALID_FILE: return "Ошибка: проблема с файлом";
        case MEMORY_ERROR: return "Ошибка: нехватка памяти";
        case STUDENT_NOT_FOUND: return "Студент не найден";
        default: return "Неизвестная ошибка";
    }
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

OperationStatus printAllStudents(Student **students, size_t count) {
    if (!students) {
        return INVALID_INPUT;
    }

    printf("Все студенты (%zu):\n", count);
    for (size_t i = 0; i < count; i++) {
        if (students[i]) {
            double avg = 0.0;
            calcAverage(students[i], &avg); 
            printf("%zu. %s %s (ID: %zu, группа: %s, средний: %.2f)\n",
                   i + 1, students[i]->first_name, students[i]->last_name,
                   students[i]->id, students[i]->group, avg);
        }
    }
    return SUCCESS;
}