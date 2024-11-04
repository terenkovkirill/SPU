#include <TXLib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "Read.h"
#include "Proc.h"           // Нужно подключать только для чтения файла в процессоре!

struct FileData ReadFile(const char *file_name)               //  ReadFile считывает данные из файла и запихивает нужные значения в структуру
{
    FILE *program_asm = fopen(file_name, "rb");
    assert(program_asm != NULL);

    long file_len = CalculationLen(program_asm);

    char* buffer = (char *)calloc(file_len, sizeof(char));
    fread(buffer, sizeof(char), file_len, program_asm);           //считываем файл в Buffer
    fclose(program_asm);

    int count_str = CounterStrings(buffer, file_len);

    char** dinamic_text = 0;                                     //адрес массива с указателями
    dinamic_text = (char **)calloc(count_str + 1, sizeof(char*));
    assert(dinamic_text != NULL);

    *dinamic_text = buffer;

    SetPointer(dinamic_text, buffer, file_len, count_str);

    struct FileData data;
    data.dinamic_text = dinamic_text;
    data.count_commands = count_str;

    return data;
}


struct Processors CreatCodeArray(const char *file_name)               //  ReadFile считывает данные из файла и запихивает нужные значения в структуру
{                                                                     //  Поработать над названием
    FILE *program_code = fopen(file_name, "rb");
    assert(program_code != NULL);

    long file_len = CalculationLen(program_code);

    int* buffer = (int *)calloc(file_len, sizeof(char));
    fread(buffer, sizeof(char), file_len, program_code);           //считываем файл в Buffer
    fclose(program_code);

    struct Processors data;
    data.code = buffer;

    return data;
}


int CalculationLen(FILE *text_file)            //вычисляем длину файла
{
    struct stat file_data = {};
    int file_descriptor = fileno(text_file);           //GetFileSize
    fstat(file_descriptor, &file_data);
    return file_data.st_size;
}



int CounterStrings(char* buffer, long file_len)
{
    int count_str = 0;                          //считаем кол-во строк (\n)
    for(int i = 0; i < file_len; i++)       //здесь было file_len - 1, но и без -1 работает
    {
        if (buffer[i] == '\n')
        {
            count_str++;
        }
    }

    return count_str;
}



void SetPointer(char** dinamic_text, char* buffer, long file_len, int count_str)
{
    int num_ptr = 0;
    for (int i = 0; i < file_len - 1; i++)              //расставляем указатели на строки
    {
        assert(0 <= i && i < file_len);
        assert(0 <= i + 1 && i + 1 < file_len);

        if (buffer[i] == '\r')
        {
            buffer[i] = '\0';
        }

        if (buffer[i] == '\n')
        {
            buffer[i] = '\0';
            num_ptr++;
            assert(num_ptr <= count_str);
            *(dinamic_text + num_ptr) = buffer + i + 1;
        }
    }
}
