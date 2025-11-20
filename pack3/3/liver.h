#ifndef LIVER_H
#define LIVER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

typedef struct {
    int day;
    int month;
    int year;
} Date;

typedef struct {
    size_t id;
    char *surname;
    char *name;
    char *patronymic;
    Date birth_date;
    char gender;
    double average_income;
} Liver;

Liver *createLiver(size_t id, char *surname, char *name, char *patronymic, Date date, char gender, double average_income);
void deleteLiver(Liver *liver);
Liver *copyLiver(Liver *liver);
int isValidLiver(Liver *liver);
int isValidName(char *s);
int isValidDate(Date date);
int isValidGender(char gender);
int isValidIncome(double income);
int compareByAge(Liver *a, Liver *b);
int calcAge(Liver *liver);
long dateToDays(Date date);
char *liverToString(Liver *liver);
void printLiver(FILE *f, Liver *liver);
Liver *readFromFile(FILE *f);
int writeToFile(FILE *f, Liver *liver);
char* strassign(char* str);

#endif