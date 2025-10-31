typedef enum {
    SUCCESS = 0,
    FAIL,
    MEMORY_ERROR,
    NOT_FOUND
} OperationStatus;

typedef unsigned long long ull;

OperationStatus conversionToBase(const ull n, const int base, char **res);
OperationStatus findAndConvertMax(const int base, char **result, char **res9, char **res18, char **res27, char **res36);