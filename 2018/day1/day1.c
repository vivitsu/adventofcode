#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define SZ 1000

char *read_line(FILE * fp) {

    if (fp == NULL) {
        printf("Unable to open file.\n");
        exit(EXIT_FAILURE);        
    }

    int linelength = 128;
    char *linebuffer = (char *) malloc(sizeof(char) * linelength);

    int ch = fgetc(fp);
    int count = 0;

    while (ch != '\n' && ch != EOF) {
        linebuffer[count++] = ch;
        ch = fgetc(fp);
    }

    linebuffer[count] = '\0';
    char *line = (char *) malloc(sizeof(char) * (count + 1));
    strncpy(line, linebuffer, count);
    free(linebuffer);    
    return line;
}

// Returns a slice of the input string starting from `begin` to `end - 1`
const char *slice(const char * src, int begin, int end) {
    assert(end > begin);
    int length = (end - begin) + 1; // Reserve space for nul character
    int i = 0;
    char *out = (char *) malloc(sizeof(char) * length);

    for (int iter = begin; iter < end; iter++) {
        out[i] = src[iter];
        i++;
    }

    out[i] = '\0';
    return out;
} 

int main(int argc, char **argv) {
    FILE *fp;
    fp = fopen("input.txt", "r");

    if (fp == NULL) {
        printf("Unable to open input file.\n");
        return -1;
    }

    int freq_change;
    int found = 0;
    int curr_freq_index = 0;
    int num_lines = 0;
    int size = SZ;
    int result = 0;
    int loop_iter = 0;    
    int *freqs = (int *) malloc(sizeof(int) * size);
    char *line;
    char *lines[1000];
    
    while(!feof(fp)) {
        line = read_line(fp);
        lines[num_lines++] = line;        
    }    

    while (!found) {
        for (int i = 0; i < num_lines; i++) {
            char *curr_line = lines[i];
            freq_change = atoi(curr_line);
            result += freq_change;
            
            for (int iter = 0; iter < curr_freq_index && !found; iter++) {
                if (freqs[iter] == result) {
                    printf("First frequency found twice: %d\n", result);
                    found = 1;                 
                }
            }
                        
            if (curr_freq_index >= size - 1) {
                size += SZ;
                freqs = (int *) realloc(freqs, sizeof(int) * size);

                if (freqs == NULL) {
                    printf("Realloc failed. Exiting...\n");
                    exit(EXIT_FAILURE);
                }
            }
            
            freqs[curr_freq_index++] = result;
            //printf("vals[%d]: %d\n", curr_freq_index, result);
        }        
        loop_iter++;
        if (loop_iter == 1) printf("Result: %d\n", result);
    }

    free(freqs);
    fclose(fp);
    return 0;    
}
