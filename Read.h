#ifndef READ_H
#define READ_H
#include <TXLib.h>
#include <stdio.h>


struct FileData
{
    char** dinamic_text;
    int count_commands;
};


int CalculationLen(FILE *text_file);
int CounterStrings(char* buffer, long file_len);
void SetPointer(char** dinamic_text, char* buffer, long file_len, int count_str);
struct FileData ReadFile(const char* file_name);
struct Processors CreatCodeArray(const char *file_name);


#endif

