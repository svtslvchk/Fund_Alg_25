#include "operations.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

static void justify_line(const char *line, char *out) {
    char temp[MAX_BUFFER];
    strncpy(temp, line, MAX_BUFFER - 1);
    temp[MAX_BUFFER - 1] = '\0';

    char *words[1000];
    int wcount = 0;

    char *tok = strtok(temp, " ");
    while (tok && wcount < (int)(sizeof(words)/sizeof(words[0]))) {
        words[wcount++] = tok;
        tok = strtok(NULL, " ");
    }

    if (wcount <= 1) {
        strncpy(out, line, WIDTH);
        out[WIDTH] = '\0';
        return;
    }

    int total_letters = 0;
    for (int i = 0; i < wcount; ++i) {
        total_letters += (int)strlen(words[i]);
    }

    int total_spaces = WIDTH - total_letters;
    if (total_spaces < 0) {
        total_spaces = 0;
    } 

    int gaps = wcount - 1;
    int base = total_spaces / gaps;
    int extra = total_spaces % gaps;

    out[0] = '\0';
    for (int i = 0; i < wcount; ++i) {
        strncat(out, words[i], WIDTH - strlen(out));
        if (i < gaps) {
            int add = base + (extra > 0 ? 1 : 0);
            if (extra > 0) {
                extra--;
            }

            for (int s = 0; s < add; ++s) {
                strncat(out, " ", WIDTH - strlen(out));
            }
        }
    }

    out[WIDTH] = '\0';
}

OperationStatus process_file(const char *input_path, const char *output_path) {
    if (!input_path || !output_path) {
        return FAIL;
    }

    FILE *fin = fopen(input_path, "r");
    FILE *fout = fopen(output_path, "w");
    if (!fin || !fout) {
        if (fin) {
            fclose(fin);
        }

        if (fout) {
            fclose(fout);
        }

        return FAIL;
    }

    char buffer[MAX_BUFFER];
    while (fgets(buffer, MAX_BUFFER, fin)) {
        size_t full_len = strlen(buffer);
        if (full_len > 0 && buffer[full_len - 1] == '\n') {
            buffer[full_len - 1] = '\0';
            full_len--;
        }

        if ((int)full_len <= WIDTH) {
            if (fprintf(fout, "%s\n", buffer) < 0) {
                fclose(fin); 
                fclose(fout);
                return FAIL;
            }

            continue;
        }

        char *start = buffer;
        while (*start) {
            int remain = (int)strlen(start);
            if (remain == 0) break;

            if (remain <= WIDTH) {
                if (strchr(start, ' ')) {
                    char out[WIDTH + 1];
                    justify_line(start, out);
                    if (fprintf(fout, "%s\n", out) < 0) {
                        fclose(fin); 
                        fclose(fout); 
                        return FAIL;
                    }
                } else {
                    if (fprintf(fout, "%s\n", start) < 0) {
                        fclose(fin); 
                        fclose(fout); 
                        return FAIL;
                    }
                }
                break;
            }

            int cut = WIDTH;
            while (cut > 0 && start[cut] != ' ' && start[cut] != '\0') {
                cut--;
            }

            if (cut == 0) {
                cut = WIDTH;
            }

            char chunk[MAX_BUFFER];
            if (cut > 0) {
                strncpy(chunk, start, cut);
                chunk[cut] = '\0';
            } else {
                chunk[0] = '\0';
            }

            int e = (int)strlen(chunk) - 1;
            while (e >= 0 && isspace((unsigned char)chunk[e])) {
                chunk[e] = '\0';
                e--;
            }

            if (strchr(chunk, ' ')) {
                char out[WIDTH + 1];
                justify_line(chunk, out);
                if (fprintf(fout, "%s\n", out) < 0) {
                    fclose(fin); 
                    fclose(fout); 
                    return FAIL;
                }
            } else {
                if (fprintf(fout, "%s\n", chunk) < 0) {
                    fclose(fin); 
                    fclose(fout); 
                    return FAIL;
                }
            }

            start += cut;
            while (*start && isspace((unsigned char)*start)) {
                start++;
            }
        } 
    } 

    fclose(fin);
    fclose(fout);
    return SUCCESS;
}
