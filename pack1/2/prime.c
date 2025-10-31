#include "prime.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

int isPrime(const ull n) {
    if (n < 2) {
        return 0;
    }

    if (n == 2) {
        return 1;
    }

    ull x = (ull)sqrt(n) + 1;
    for (ull i = 3; i <= x; i += 2) {
        if (n % i == 0) {
            return 0;
        }
    }

    return 1;

}

PrimeStatus findPrimeByNumber(const int n, ull *res) {
    if (!res) {
        return INVALID_ARGS;
    }

    if (n <= 0) {
        return NO_RESULT;
    }
    
    if (n == 1) {
        *res = 2;
        return SUCCES;
    }

    ull current = 3;
    int i = 1;
    while (i < n) {
        if (isPrime(current)) {
            i++;
        }

            if (i == n) {
                *res = current;
                return SUCCES;
            }

        current += 2;
    }

    return NO_RESULT;
}

PrimeStatus findPrimes(const int t, ull **results, PrimeStatus **statuses) {
    if (t <= 0) {
        return NO_RESULT;
    }

    if (!results || !statuses) {
        return INVALID_ARGS;
    }

    *statuses = (PrimeStatus *)malloc(sizeof(PrimeStatus) * t);
    *results = (ull *)malloc(sizeof(ull) * t);
    if (!(*results) || !(*statuses)) {
        free(*statuses);
        free(*results);
        *results = NULL;
        *statuses = NULL;
        return MEMORY_ERROR;
    }

    int n;
    for (int i = 0; i < t; i++) {
        scanf("%d", &n);
        (*statuses)[i] = findPrimeByNumber(n, &((*results)[i]));
        if ((*statuses)[i] != SUCCES) {
            (*results)[i] = 0;
        }
    }

    return SUCCES;
}