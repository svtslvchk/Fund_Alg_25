typedef enum {
    SUCCES = 0,
    FAIL,
    MEMORY_ERROR
} OperationsStatus;

OperationsStatus removeArabicDigits(const char *input_filename, const char *output_filename);
OperationsStatus countLatinLettersinLines(const char *input_filename, const char *output_filename);
OperationsStatus notLatinArabicSpace(const char *input_filename, const char *output_filename);
OperationsStatus notArabicToASCII(const char *input_filename, const char *output_filename);