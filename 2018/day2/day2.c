#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_line(FILE *fp) {
    int count = 0;
    int line_size = 128; // characters
    char *linebuffer = (char *) malloc(sizeof(char) * line_size);
    char *line;

    char ch = fgetc(fp);

    while(ch != '\n' || ch != EOF) {
	linebuffer[count++] = ch;

	if (count >= line_size - 1) {
	    line_size += 128;
	    linebuffer = (char *) realloc(linebuffer, sizeof(char) * line_size);
	}

	ch = fgetc(fp);
    }

    linebuffer[count] = '\0';
    line = (char *) malloc(sizeof(char) * (count + 1));
    strncpy(line, linebuffer, count);
    free(linebuffer);
    return line;
}

int main(int argc, char **argv) {
    FILE *fp = fopen("input.txt", "r");

    if (!fp) {
	printf("Error while opening file.\n");
	exit(EXIT_FAILURE);
    }

    int num_lines = 0;
    char *lines[1000];
    
    while(!feof(fp)) {
	lines[num_lines++] = read_line(fp);
    }

    fclose(fp);
    exit(EXIT_SUCCESS);
}
