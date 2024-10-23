//#include <TXLib.h>
#include <stdio.h>
#include <string.h>

//#include "Stack.h"
//#include "Checkout.h"

int main(int argc, const char* argv[])  //файлы для считывания и записи в dump
{
    if (argc != 3) {
        printf("Erroneous number of elements \n");
    }


    FILE* program_asm = fopen(argv[1], "rb");
    FILE* program_code = fopen(argv[2], "wb");



    while(1)
    {
        char cmd[50] = "";

        fscanf(program_asm, "%s", cmd);

        if (strcmp(cmd, "push") == 0) {
            double arg = NAN;
            fscanf(program_asm, "%lg", &arg);
            fprintf(program_code, "%d %lg \n", 1, arg); 

            printf("Read push \n");
        }
        
        else if (strcmp(cmd, "add") == 0) {
            fprintf(program_code, "%d \n", 2);

            printf("Read add \n");
        }

        else if (strcmp(cmd, "sub") == 0) {
            fprintf(program_code, "%d \n", 3);
        }

        else if (strcmp(cmd, "div") == 0) {
            fprintf(program_code, "%d \n", 4);
        }

        else if (strcmp(cmd, "out") == 0) {
            fprintf(program_code, "%d \n", 5);
        }

        else if (strcmp(cmd, "mul") == 0) {
            fprintf(program_code, "%d \n", 7);
        }

        else if (strcmp(cmd, "jb") == 0) {
            fprintf(program_code, "%d \n", 9);

            printf("Read jb \n");
            printf("%s \n", cmd);
        }

        else if (strcmp(cmd, "pop ax") == 0) {
            fprintf(program_code, "%d \n", 10);
        }

        else if (strcmp(cmd, "pushr ax") == 0) {
            fprintf(program_code, "%d \n", 11);
        }

        else if (strcmp(cmd, "hlt") == 0) {
            fprintf(program_code, "%d \n", 0);
            break;
        }

        else {
            printf("SNTXERR: ( %s ) \n", cmd);
            break;
        }
    }

    printf("It works \n");
    fclose(program_asm);
    fclose(program_code);
}


/*
1) Метки и хороший процессор

2) fread как  в Онегине

*/

//feof() считывает файл до конца
//while(!feof(указателя на файл))

//Если установить формат  считывания wb вместо r считывания, то также нет записей в PROGRAM_CODE.TXT, но вдобавок очищается PROGRAM_ASM.TXT
