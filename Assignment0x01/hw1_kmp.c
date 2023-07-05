#include <stdio.h>
#include <string.h>
#define SMAXSIZE 10000000+5
#define PMAXSIZE 3000+5
char string[SMAXSIZE];
char pattern[PMAXSIZE];
int failure_function[PMAXSIZE]; // An array to store the values ​​of the pattern's failure function
int matching_indices[SMAXSIZE]; // Array to store matching indices

/* Function */
void fail(char* pat);
int kmp(char* str, char* pat);
void read_file(const char* filename, char* buffer, int buffer_size);
void write_file(const char* filename, int cnt, int* matching_indices);
int file_exists(const char* filename);

/* Main */
int main()
{
    if (!file_exists("string.txt") || !file_exists("pattern.txt"))
    {
        printf("The string file does not exist.\n");
        return 1;
    }

    read_file("string.txt", string, SMAXSIZE);
    read_file("pattern.txt", pattern, PMAXSIZE);

    fail(pattern);
    int cnt = kmp(string, pattern);

    write_file("result_kmp.txt", cnt, matching_indices);

    return 0;
}

// Computes the failure function for the given pattern
void fail(char* pat)
{
    int patternlength = strlen(pat);
    failure_function[0] = 0;
    int j = 0;
    int i;
    for (i = 1; i < patternlength; i++)
    {
        while (j > 0 && pat[i] != pat[j])
            j = failure_function[j - 1];
        if (pat[i] == pat[j])
            failure_function[i] = ++j;
        else
            failure_function[i] = 0;
    }
}

// KMP algorithm
int kmp(char* str, char* pat)
{
    int stringlength = strlen(str), patternlength = strlen(pat);
    int cnt = 0;
    int i = 0; // 인덱스 변수
    int j = 0;
    for (j = 0; j < stringlength; j++) {
        while (i > 0 && pat[i] != str[j]) {
            i = failure_function[i - 1];
        }
        if (pat[i] == str[j]) {
            i++;
        }
        if (i == patternlength) {
            matching_indices[cnt++] = j - patternlength + 1;
            i = failure_function[i - 1];
        }
    }

    return cnt;
}


// Reads the file into a buffer
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

// Write the result
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