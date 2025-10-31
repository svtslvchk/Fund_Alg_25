typedef enum {
    SUCCESS = 0,
    FAIL = 1,
    MEMORY_ERROR = 2,
    FILE_ERROR = 3
} OperationStatus;

OperationStatus convertFile(const char *input_filename, const char *output_filename);