#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "liver.h"

Liver *createLiver(size_t id, char *surname, char *name, char *patronymic, Date date, char gender, double average_income) {
    if (!surname || !strlen(surname) || !isValidName(surname)) {
        fprintf(stderr, "Invalid surname\n");
        return NULL;
    }

    if (!name || !strlen(name) || !isValidName(name)) {
        fprintf(stderr, "Invalid name\n");
        return NULL;
    }

    if (patronymic && !isValidName(patronymic)) {
        fprintf(stderr, "Invalid patronymic\n");
        return NULL;
    }

    if (!isValidDate(date)) {
        fprintf(stderr, "Invalid date\n");
        return NULL;;
    }

    if (!isValidGender(gender)) {
        fprintf(stderr, "Invalid gender\n");
        return NULL;
    }

    if (!isValidIncome(average_income)) {
        fprintf(stderr, "Invalid income\n");
        return NULL;
    }

    Liver *liver = (Liver *)malloc(sizeof(Liver));
    if (!liver) {
        fprintf(stderr, "Memory allocation error\n");
        return NULL;
    }

    liver->name = strassign(name);
    liver->surname = strassign(surname);
    liver->patronymic = strassign(patronymic);
    if (!liver->name || !liver->surname || !liver->patronymic) {
        fprintf(stderr, "Assignment string error\n");
        return NULL;
    }

    liver->id = id;
    liver->birth_date = date;
    liver->gender = gender;
    liver->average_income = average_income;

    return liver;
}

void deleteLiver(Liver *liver) {
    if (!liver) {
        return;
    }

    free(liver->surname);
    free(liver->name);
    free(liver->patronymic);
    free(liver);
}

Liver *copyLiver(Liver *liver) {
    if (!liver) {
        return NULL;
    }

    return createLiver(liver->id, liver->surname, liver->name, liver->patronymic, liver->birth_date, liver->gender, liver->average_income);
}

int isValidLiver(Liver *liver) {
    if (!liver) {
        return 0;
    }

    return liver->id > 0 &&
           liver->surname && strlen(liver->surname) > 0 && isValidName(liver->surname) &&
           liver->name && strlen(liver->name) > 0 && isValidName(liver->name) &&
           liver->patronymic && isValidName(liver->patronymic) &&
           isValidDate(liver->birth_date) &&
           isValidGender(liver->gender) &&
           isValidIncome(liver->average_income);
}

int isValidName(char *s) {
    if (!s) {
        return 1;
    }

    for (int i = 0; s[i]; i++) {
        if (!isalpha(s[i])) {
            return 0;
        }
    }

    return 1;
}

int isValidDate(Date date) {
    if (date.year < 1 || date.year > 2025) {
        return 0;
    }

    if (date.month < 1 || date.month > 12) {
        return 0;
    }

    int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (date.month == 2) {
        int is_leap = (date.year % 4 == 0 && date.year % 100 != 0) || (date.year % 400 == 0);
        if (date.day < 1 || date.day > (28 + is_leap)) {
            return 0;
        } else {
            if (date.day < 1 || date.day > days_in_month[date.month - 1]) {
                return 0;
            }
        }
    }

    return 1;
}

int isValidGender(char gender) {
    return gender == 'M' || gender == 'W';
}

int isValidIncome(double income) {
    return income >= 0.0;
}

int compareByAge(Liver *a, Liver *b) {
    return (int)(a->id - b->id);
}

int calcAge(Liver *liver) {
    if (!liver) {
        return 0;
    }
    
    time_t now = time(NULL);
    struct tm* current_time = localtime(&now);
    
    int age = current_time->tm_year + 1900 - liver->birth_date.year;
    
    if (current_time->tm_mon + 1 < liver->birth_date.month ||
        (current_time->tm_mon + 1 == liver->birth_date.month && 
         current_time->tm_mday < liver->birth_date.day)) {
        age--;
    }
    
    return age;
}

long dateToDays(Date date) {
    return date.year * 365L + date.month * 30L + date.day;
}

char *liverToString(Liver *liver) {
    if (!liver) return NULL;
    
    char* str = (char*)malloc(256);
    if (!str) return NULL;
    
    snprintf(str, 256, "%zu,%s,%s,%s,%02d.%02d.%d,%c,%.2f",
             liver->id, liver->surname, liver->name, liver->patronymic,
             liver->birth_date.day, liver->birth_date.month, liver->birth_date.year,
             liver->gender, liver->average_income);
    
    return str;
}

void printLiver(FILE *f, Liver *liver) {
    if (!liver || !f) return;
    
    fprintf(f, "ID: %zu, Name: %s %s %s, Birth: %02d.%02d.%d, Gender: %c, Income: %.2f, Age: %d\n",
            liver->id, liver->surname, liver->name, liver->patronymic,
            liver->birth_date.day, liver->birth_date.month, liver->birth_date.year,
            liver->gender, liver->average_income, calcAge(liver));
}

Liver *readFromFile(FILE *f) {
    if (!f) return NULL;
    
    size_t id;
    char surname[100], name[100], patronymic[100];
    Date birth_date;
    char gender;
    double income;
    
    if (fscanf(f, "%zu,%99[^,],%99[^,],%99[^,],%d.%d.%d,%c,%lf",
               &id, surname, name, patronymic,
               &birth_date.day, &birth_date.month, &birth_date.year,
               &gender, &income) == 9) {
        
        return createLiver(id, surname, name, patronymic, birth_date, gender, income);
    }
    
    return NULL;
}

int writeToFile(FILE *f, Liver *liver) {
    if (!liver || !f) return 0;
    
    char* str = liverToString(liver);
    if (!str) return 0;
    
    fprintf(f, "%s\n", str);
    free(str);
    
    return 1;
}

char* strassign(char* str) {
    if (!str) {
        return NULL;
    }

    char* copy = malloc(strlen(str) + 1);
    if (copy) {
        strcpy(copy, str);
    }

    return copy;
}