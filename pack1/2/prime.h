#ifndef PRIME_H
#define PRIME_H

#include <stdbool.h>

typedef unsigned long long ull;

typedef enum {
    SUCCES = 0,
    NO_RESULT,
    INVALID_ARGS,
    MEMORY_ERROR
} PrimeStatus;

PrimeStatus findPrimeByNumber(const int n, ull *res);
PrimeStatus findPrimes(const int t, ull **results, PrimeStatus **statuses);

#endif