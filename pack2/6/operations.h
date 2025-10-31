#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <stddef.h>

#define GRADES_COUNT 5

typedef struct {
    size_t id;
    char *first_name;
    char *last_name;
    char *group;
    unsigned char *grades;
} Student;

typedef enum {
    SUCCESS = 0,
    INVALID_FILE,
    MEMORY_ERROR,
    INVALID_INPUT,
    STUDENT_NOT_FOUND,
    ERROR
} OperationStatus;

int isCorrectString(const char *s);
OperationStatus readStudentsFromFile(const char *input_filename, Student ***students, size_t *count);
OperationStatus freeStudents(Student **students, size_t count);
OperationStatus calcAverage(Student *student, double *average);
OperationStatus calcOverallAverage(Student **students, size_t count, double *overall_average);
OperationStatus findById(Student **students, size_t count, const size_t id, Student ***found, size_t *found_count);
OperationStatus findByFirstName(Student **students, size_t count, const char *first_name, Student ***found, size_t *found_count);
OperationStatus findByLastName(Student **students, size_t count, const char *last_name, Student ***found, size_t *found_count);
OperationStatus findByGroup(Student **students, size_t count, const char *group, Student ***found, size_t *found_count);
int compareById(const void *a, const void *b);
int compareByFirstName(const void *a, const void *b);
int compareByLastName(const void *a, const void *b);
int compareByGroup(const void *a, const void *b);
OperationStatus printStudentById(Student **students, size_t count, size_t id, const char *trace_filename);
OperationStatus printStudentsAboveAverage(Student **students, size_t count, const char *trace_filename);
void printMenu();
const char* getStatusMessage(OperationStatus status);
void clearInputBuffer();
OperationStatus printAllStudents(Student **students, size_t count);

#endif
