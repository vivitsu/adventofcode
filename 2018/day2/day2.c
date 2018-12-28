#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_line(FILE *fp) {
    int count = 0;
    int line_size = 128; // characters
    char *linebuffer = (char *) malloc(sizeof(char) * line_size);
    char *line;

    char ch = fgetc(fp);

    while(ch != '\n' && ch != EOF) {
	linebuffer[count++] = ch;
	ch = fgetc(fp);
    }

    linebuffer[count] = '\0';
    line = (char *) malloc(sizeof(char) * (count + 1));
    strncpy(line, linebuffer, count);
    free(linebuffer);
    return line;
}

int istwocount(char *line) {
    int alphabet[26];

    for (int k = 0; k < 26; k++) {
	alphabet[k] = 0;
    }

    for (int i = 0; line[i] != '\0'; i++) {
	alphabet[line[i] - 'a']++;
    }

    for (int j = 0; j < 26; j++) {
	if (alphabet[j] == 2) {
	    return 1;
	}
    }

    return 0;
}

int isthreecount(char *line) {
    int alphabet[26];

    for (int k = 0; k < 26; k++) {
	alphabet[k] = 0;
    }

    for (int i = 0; line[i] != '\0'; i++) {
	alphabet[line[i] - 'a']++;
    }

    for (int j = 0; j < 26; j++) {
	if (alphabet[j] == 3) {
	    return 1;
	}
    }

    return 0;
}

int xor_strings(char *str1, char *str2) {
    int result = 0;
    // assuming that both strings are of the same length	    
    for (int k = 0;  k < strlen(str1); k++) {
	if (!(str1[k] - str2[k])) {
	    result += 0;
	} else {
	    result += 1;
	}
    }

    return result;
}
    

int main(int argc, char **argv) {
    FILE *fp = fopen("input.txt", "r");

    if (!fp) {
	printf("Error while opening file.\n");
	exit(EXIT_FAILURE);
    }

    int num_lines = 0;
    char *lines[1000];
    int two_count = 0, three_count = 0;
    
    while(!feof(fp)) {
	char *line = read_line(fp);

	if (istwocount(line)) {
	    two_count++;
	}

	if (isthreecount(line)) {
	    three_count++;
	}
	
	lines[num_lines++] = line;
    }
    printf("checksum: %d\n", two_count * three_count);    

    for (int i = 0; i < num_lines; i++) {
	for (int j = i+1; j < num_lines; j++) {
	    int result = xor_strings(lines[i], lines[j]);
	    if (result == 1) {	      
		printf("%s and %s differ by %d characters\n", lines[i], lines[j], result);
	    }
	}
    }

    fclose(fp);
    exit(EXIT_SUCCESS);
}
