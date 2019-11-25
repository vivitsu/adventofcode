#include <stdio.h>
#include <string.h>

#define MAX_LINESZ 20

typedef struct cuboid
{
    int length;
    int width;
    int height;
} cuboid;

char* read_file(const char* path)
{
    FILE* fp;
    fopen_s(&fp, path, "rb");
    if (fp == NULL)
    {
        perror("Could not open input file\n");
        exit(1);
    }
    fseek(fp, 0, SEEK_END);
    long sz = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char* buf = (char*)malloc(sz + 1);
    if (!buf)
    {
        perror("Could not allocate memory for buffer\n");
        exit(1);
    }
    if (fread(buf, sz, 1, fp) != 1)
    {
        fclose(fp);
        free(buf);
        return NULL;
    }
    fclose(fp);
    buf[sz] = 0;
    return buf;
}

int num_lines_in_file(char* buf)
{
    int num_lines = 0;
    for (int i = 0; buf[i] != 0; i++)
    {
        if (buf[i] == '\n')
        {
            num_lines++;
        }
    }
    return num_lines;
}

void read_lines(char* buf, char** lines)
{
    int curr_line = 0;
    int curr_line_sz = 0;
    int start = 0;
    for (int i = 0; buf[i] != 0; i++)
    {
        if (buf[i] == '\n')
        {
            char line[MAX_LINESZ];
            int k = 0;
            for (int j = start; j < i; j++)
            {
                line[k] = buf[j];
                k++;
            }
            line[k] = 0;
            printf("Line: %s\n", line);
            curr_line_sz = i - start + 1;
            // FIXME - Here be dragons!!!
            memcpy_s(lines[curr_line], curr_line_sz, line, curr_line_sz);
            printf("Current line: %s\n", lines[curr_line]);
            curr_line++;
            start = i + 1;
        }
    }
}

int main()
{
    char* buf = read_file("day2_input.txt");
    int num_lines = num_lines_in_file(buf);
    printf("Number of lines in file: %d\n", num_lines);
    char** lines = (char**)malloc(sizeof(char)*num_lines*MAX_LINESZ);
    read_lines(buf, lines);
    for (int i = 0; i < num_lines; i++)
    {
        printf("%d: %s\n", i+1, lines[i]);
    }
    return 0;
}