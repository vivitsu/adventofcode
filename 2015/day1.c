#include <stdio.h>

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

int main()
{
    char* buf = read_file("day1_input.txt");

    int count = 0;
    int first_basement_entry = 0; // False
    for (int i = 0; buf[i] != 0; i++)
    {
        if (count == -1 && !first_basement_entry)
        {
            printf("Position when entering basement: %d\n", i);
            first_basement_entry = 1;
        }
        if (buf[i] == '(')
        {
            count++;
        }
        else if (buf[i] == ')')
        {
            count--;
        }
    }
    printf("Floor: %d\n", count);
    return 0;
}