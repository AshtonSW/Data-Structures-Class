#include <stdio.h>
#include <string.h>
#define SMAXSIZE 10000000+5
#define PMAXSIZE 3000+5

/* global variation */
char string[SMAXSIZE];
char pattern[PMAXSIZE];
int matching_indices[SMAXSIZE];

/* Function */
int naive(char* str, char* pat);
void read_file(const char* filename, char* buf, int buf_size);
void write_file(const char* filename, int cnt, int* matchidx);
int file_exists(const char* filename);

/* main */
int main()
{   
    if (!file_exists("string.txt") || !file_exists("pattern.txt"))
    {
        printf("The string file does not exist.\n");
        return 1;
    }

    read_file("string.txt", string, SMAXSIZE);
    read_file("pattern.txt", pattern, PMAXSIZE);

    int cnt = naive(string, pattern);

    write_file("result_naive.txt", cnt, matching_indices);

    return 0;
}

/* Read file content and remove newline character */
void read_file(const char* filename, char* buf, int buf_size)
{
    FILE* file = fopen(filename, "r");
    if (file == NULL)
    {
        return;
    }
    if (fgets(buf, buf_size, file) != NULL)
    {
        size_t len = strlen(buf);
        if (len > 0 && buf[len - 1] == '\n')
        {
            buf[len - 1] = '\0';
        }
    }
    fclose(file);
}

/* Write result to file */
void write_file(const char* filename, int cnt, int* matching_indices)
{
    int i;
    FILE* file = fopen(filename, "w");
    fprintf(file, "%d\n", cnt);
    for (i = 0; i < cnt; i++) {
    fprintf(file, "%d ", matching_indices[i]);
    }
    fclose(file);
}
/* Naive pattern matching algorithm */
int naive(char* str, char* pat)
{
    int stringlength = strlen(str), patternlength = strlen(pat);
    int cnt = 0;
    for (int i = 0; i <= stringlength - patternlength; i++){
        int match = 1;
        for (int j = 0; j < patternlength; j++){
            if (str[i + j] != pat[j]){
                match = 0;
                break;
            }
        }
        if (match)
            matching_indices[cnt++] = i;
    }
    return cnt;
}

// Check if file exists
int file_exists(const char* filename)
{
    FILE* file = fopen(filename, "r");
    if (file != NULL)
    {
        fclose(file);
        return 1;
    }
    return 0;
}