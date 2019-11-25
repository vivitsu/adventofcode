#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

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
            curr_line_sz = i - start + 1;
            lines[curr_line] = malloc(sizeof(char)*curr_line_sz);
            strcpy_s(lines[curr_line], curr_line_sz, line);
            curr_line++;
            start = i + 1;
        }
    }
}

cuboid* get_cuboids(char** lines, int num_lines)
{
    uint32_t result = 0;
    cuboid* cuboids = malloc(sizeof(cuboid)*num_lines);
    for (int i = 0; i < num_lines; i++)
    {
        char* line = lines[i];
        cuboid c;
        sscanf(line, "%dx%dx%d", &c.length, &c.width, &c.height);
        cuboids[i].length = c.length;
        cuboids[i].width = c.width;
        cuboids[i].height = c.height;
    }
    return cuboids;
}

uint32_t ribbon_needed(cuboid* cuboids, int num_lines)
{
    uint32_t result = 0;
    for (int i = 0; i < num_lines; i++)
    {
        int perimeter1 = 2*cuboids[i].length + 2*cuboids[i].width;
        int perimeter2 = 2*cuboids[i].width + 2*cuboids[i].height;
        int perimeter3 = 2*cuboids[i].height + 2*cuboids[i].length;
        int min_perimeter = min(min(perimeter1, perimeter2), perimeter3); 
        result += min_perimeter + (cuboids[i].length*cuboids[i].width*cuboids[i].height);
    }
    return result;
}

uint32_t wrapping_paper_needed(cuboid* cuboids, int num_lines)
{
    uint32_t result = 0;
    for (int i = 0; i < num_lines; i++)
    {
        int lw = cuboids[i].length * cuboids[i].width;
        int wh = cuboids[i].width * cuboids[i].height;
        int hl = cuboids[i].height * cuboids[i].length;
        int min_side_area = min(min(lw, wh), hl);
        result += 2*lw + 2*wh + 2*hl + min_side_area;
    }
    return result;
}

int main()
{
    char* buf = read_file("day2_input.txt");
    int num_lines = num_lines_in_file(buf);
    printf("Number of lines in file: %d\n", num_lines);
    char** lines = malloc(sizeof(char*)*num_lines);
    read_lines(buf, lines);
    cuboid* cuboids = get_cuboids(lines, num_lines);
    uint32_t wrapping_paper_sz = wrapping_paper_needed(cuboids, num_lines);
    uint32_t ribbon_sz = ribbon_needed(cuboids, num_lines);
    printf("Wrapping Paper Size: %d\n", wrapping_paper_sz);
    printf("Ribbon Size: %d\n", ribbon_sz);
    for (int i = 0; i < num_lines; i++)
    {
        free(lines[i]);
    }
    free(lines);
    free(cuboids);
    return 0;
}