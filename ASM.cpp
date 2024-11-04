#include <TXLib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "Read.h"
#include "Enum.h"

const int NUM_LABELS = 100;

void Assembler(struct FileData *asmb, const char* filename);
void ReadPushArgType(char* cmd2, int* code, int* ip);
void ReadPopArgType(char* cmd2, int* code, int* ip);

struct Labels 
{
    int* addr;
    int name;
};



int main(int argc, const char* argv[])  //файлы для считывания и записи в dump
{
    if (argc != 3) {
        printf("Erroneous number of elements \n");
        return 0;
    }

    struct FileData asmb = ReadFile(argv[1]);

    //printf("Number of commands %d \n", asmb.count_commands);

    Assembler(&asmb, argv[2]);

    printf("It works \n");

    return 0;
}



void Assembler(struct FileData *asmb, const char* filename)
{
    FILE* program_code = fopen(filename, "wb");

    int ip = 0, cur_cmd = 0;
    int code[asmb->count_commands * 2];      //фиговое объявление массива!

    // struct Labels labels[NUM_LABELS];

    // char string[50] = "";
    // int cur_label = 0;

    // while(1)
    // {
    //     sscanf(asmb->dinamic_text[cur_cmd], "%s", string);

    //     if (strcmp(string, "") == 0) {
    //         cur_cmd++;
    //     }

    //     else if (strcmp(string, "SECOND") == 0) {
    //         cur_cmd++;
    //     }

    //     else if (strcmp(string, "THIRD") == 0) {
    //         cur_cmd++;
    //     }

    //     if (strcmp(string, "hlt") == 0) {
    //         break;
    //     }
    // }

    // cur_cmd = 0;

    char cmd[50] = "";             //name of command
    char cmd2[50] = "";            //type of command
    int arg = 0;                   //integer argument of command

    while(1)
    {
        int num_param = sscanf(asmb->dinamic_text[cur_cmd], "%s %d", cmd, &arg);

        if (strcmp(cmd, "push") == 0) {
            if (num_param == 2) {
                code[ip++] = (PUSH & OPCODE_MSK) | (ARG_TYPE_MSK & DATA_ARG);
                code[ip++] = arg;
            }
            
            else {
                sscanf(asmb->dinamic_text[cur_cmd], "%s %s", cmd, cmd2);
                ReadPushArgType(cmd2, code, &ip);
            } 

            cur_cmd++;
        }

        else if (strcmp(cmd, "pop") == 0) {
            if (num_param == 2) {
                code[ip++] = (POP & OPCODE_MSK) | (DATA_ARG & ARG_TYPE_MSK);
                code[ip++] = arg;
            }
            
            else {
                sscanf(asmb->dinamic_text[cur_cmd], "%s %s", cmd, cmd2);
                ReadPopArgType(cmd2, code, &ip);
            }

            cur_cmd++; 
        }
        
        else if (strcmp(cmd, "add") == 0) {
            code[ip++] = ADD;
            cur_cmd++;
        }

        else if (strcmp(cmd, "sub") == 0) {
            code[ip++] = SUB;
            cur_cmd++;
        }

        else if (strcmp(cmd, "div") == 0) {
            code[ip++] = DIV;
            cur_cmd++;
        }

        else if (strcmp(cmd, "out") == 0) {
            code[ip++] = OUTPUT;
            cur_cmd++;
        }

        else if (strcmp(cmd, "mul") == 0) {
            code[ip++] = MUL;
            cur_cmd++;
        }

        else if (strcmp(cmd, "jb") == 0) {
            code[ip++] = JB;
            cur_cmd++;
        }

        else if (strcmp(cmd, "hlt") == 0) {
            code[ip++] = HLT;
            break;
        }

        else {
            printf("SNTXERR: ( %s ) \n", cmd);
            break;
        }
    }

    fwrite(code, sizeof(int), ip, program_code);

    fclose(program_code);
}

void ReadPushArgType(char* cmd2, int* code, int* ip)
{
    if (strcmp(cmd2, "ax") == 0) {
        code[(*ip)++] = (PUSH & OPCODE_MSK) | (REG_ARG & ARG_TYPE_MSK);
        code[(*ip)++] = AX;
    }

    else if (strcmp(cmd2, "bx") == 0) {
        code[(*ip)++] = (PUSH & OPCODE_MSK) | (REG_ARG & ARG_TYPE_MSK);
        code[(*ip)++] = BX;
    }

    else {
        printf("SNTXERROR in command PUSH ( %s ) \n", cmd2);
    }
}


void ReadPopArgType(char* cmd2, int* code, int* ip)
{
    if (strcmp(cmd2, "ax") == 0) {
        code[(*ip)++] = (POP & OPCODE_MSK) | (REG_ARG & ARG_TYPE_MSK);
        code[(*ip)++] = AX;
    }

    else if (strcmp(cmd2, "bx") == 0) {
        code[(*ip)++] = (POP & OPCODE_MSK) | (REG_ARG & ARG_TYPE_MSK);
        code[(*ip)++] = BX;
    }

    else {
        printf("SNTXERROR in command POP ( %s ) \n", cmd2);
    }
}



/*
1) Метки и хороший процессор

2) fread как  в Онегине

*/

//feof() считывает файл до конца
//while(!feof(указателя на файл))

//Если установить формат  считывания wb вместо r считывания, то также нет записей в PROGRAM_CODE.TXT, но вдобавок очищается PROGRAM_ASM.TXT



///////DFGDS