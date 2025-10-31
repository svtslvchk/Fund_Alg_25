#include "operations.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

void test_convertFile();

int main() {
    test_convertFile();
    printf("All convertFile tests passed successfully!\n");
    return 0;
}

void test_convertFile() {
    FILE *f = fopen("tmp_in.txt", "w");
    assert(f != NULL);
    fprintf(f, "1010 F 123\nhello 123 Z9\n0005\n");
    fprintf(f, "000123\n");          
    fprintf(f, "2672672?2782\n");    
    fclose(f);

    assert(convertFile("tmp_in.txt", "tmp_out.txt") == SUCCESS);

    f = fopen("tmp_out.txt", "r");
    assert(f != NULL);
    char line[256];

    int found1010 = 0, foundF = 0, found123 = 0, foundHello = 0, foundZ9 = 0, found5 = 0, found000123 = 0;
    int foundBad = 0; 

    while (fgets(line, sizeof(line), f)) {
        if (strstr(line, "1010 2 10")) found1010 = 1;
        if (strstr(line, "F 16 15")) foundF = 1;
        if (strstr(line, "123 4 27")) {
            if (!found123) found123 = 1;
            else found000123 = 1; 
        }
        if (strstr(line, "hello 25 6873049")) foundHello = 1;
        if (strstr(line, "Z9 36 1269")) foundZ9 = 1;
        if (strstr(line, "5 6 5")) found5 = 1;
        if (strstr(line, "2672672") || strstr(line, "2782")) foundBad = 1; 
    }
    fclose(f);

    remove("tmp_in.txt");
    remove("tmp_out.txt");

    assert(found1010);
    assert(foundF);
    assert(found123);
    assert(foundHello);
    assert(foundZ9);
    assert(found5);
    assert(found000123);
    assert(!foundBad); 
}
