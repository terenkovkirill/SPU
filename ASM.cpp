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
void ReadArgType(char*cmd, char* cmd2, int* code, int* ip);
void FillArrayLabels(struct FileData* asmb, struct Labels* labels[]);
void PutLabels(char* cmd, char* cmd2, int* code, int* ip, struct Labels* labels[]);

struct Labels 
{
    int index;
    char name[];
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
    assert(asmb != NULL);

    FILE* program_code = fopen(filename, "wb");

    int ip = 0, cur_cmd = 0;
    int code[asmb->count_commands * 2];      //фиговое объявление массива!

    struct Labels labels[NUM_LABELS];
    FillArrayLabels(asmb, (Labels **)labels);       //правильно ли передаю массив структур

    char cmd[50] = "";             //name of command
    char cmd2[50] = "";            //type of command
    int arg = 0;                   //integer argument of command

    while(1)
    {
        int num_param = sscanf(asmb->dinamic_text[cur_cmd], "%s %d", cmd, &arg);

        if (strchr(cmd, ':') == NULL) 
        {
            continue;
        }
               
        if (strcmp(cmd, "push") == 0) {

            code[ip++] = PUSH;

            if (num_param == 2) {
                code[ip++] = STACK_ARG;
                code[ip++] = arg;
            }
            
            else {
                sscanf(asmb->dinamic_text[cur_cmd], "%s %s", cmd, cmd2);
                ReadArgType(cmd, cmd2, code, &ip);
            } 

            cur_cmd++;
        }

        else if (strcmp(cmd, "pop") == 0) {

            code[ip++] = POP;

            if (num_param == 2) {
                code[ip++] = STACK_ARG;
                code[ip++] = arg;
            }
            
            else {
                sscanf(asmb->dinamic_text[cur_cmd], "%s %s", cmd, cmd2);
                ReadArgType(cmd, cmd2, code, &ip);
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

        else if (strcmp(cmd, "jmp") == 0){
            code[ip++] = JMP;
            sscanf(asmb->dinamic_text[cur_cmd], "%s %s", cmd, cmd2);
            PutLabels(cmd, cmd2, code, &ip, (Labels **)labels);
            cur_cmd++;
        }

        else if (strcmp(cmd, "ja") == 0){
            code[ip++] = JA;
            sscanf(asmb->dinamic_text[cur_cmd], "%s %s", cmd, cmd2);
            PutLabels(cmd, cmd2, code, &ip, (Labels **)labels);
            cur_cmd++;
        }

        else if (strcmp(cmd, "jb") == 0){
            code[ip++] = JB;
            sscanf(asmb->dinamic_text[cur_cmd], "%s %s", cmd, cmd2);
            PutLabels(cmd, cmd2, code, &ip, (Labels **)labels);
            cur_cmd++;
        }

        else if (strcmp(cmd, "je") == 0){
            code[ip++] = JE;
            sscanf(asmb->dinamic_text[cur_cmd], "%s %s", cmd, cmd2);
            PutLabels(cmd, cmd2, code, &ip, (Labels **)labels);
            cur_cmd++;
        }

        else if (strcmp(cmd, "jae") == 0){
            code[ip++] = JAE;
            sscanf(asmb->dinamic_text[cur_cmd], "%s %s", cmd, cmd2);
            PutLabels(cmd, cmd2, code, &ip, (Labels **)labels);
            cur_cmd++;
        }

        else if (strcmp(cmd, "jbe") == 0){
            code[ip++] = JBE;
            sscanf(asmb->dinamic_text[cur_cmd], "%s %s", cmd, cmd2);
            PutLabels(cmd, cmd2, code, &ip, (Labels **)labels);
            cur_cmd++;
        }

        else if (strcmp(cmd, "jne") == 0){
            code[ip++] = JNE;
            sscanf(asmb->dinamic_text[cur_cmd], "%s %s", cmd, cmd2);
            PutLabels(cmd, cmd2, code, &ip, (Labels **)labels);
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

    // int cur_ind = 0;            //для текстового файла и отладки на нём 
    // while(1)
    // {
    //     fprintf(program_code, "%d \n", code[cur_ind]);
    //     if (code[cur_ind] == HLT)
    //         break;
        
    //     cur_ind++;
    // }

    fclose(program_code);
}


void ReadArgType(char* cmd, char* cmd2, int* code, int* ip)
{
    if (strcmp(cmd2, "ax") == 0) {
        code[(*ip)++] = REG_ARG;
        code[(*ip)++] = AX;
    }

    else if (strcmp(cmd2, "bx") == 0) {
        code[(*ip)++] = REG_ARG;
        code[(*ip)++] = BX;
    }

    else {
        printf("SNTXERROR in command %s: ( %s ) \n", cmd, cmd2);
    }
}


void PutLabels(char* cmd, char* cmd2, int* code, int* ip, struct Labels* labels[])
{
    assert(labels != NULL);     
    assert(code != NULL);           //нужны ли ещё assert !
    assert(cmd != NULL);

    int cnt = 0;
    while (strcmp(labels[cnt]->name, "0") != 0)
    {
        if (strcmp(cmd2, labels[cnt]->name))
        {
            code[(*ip)++] = labels[cnt]->index;  
            return;
        }
    }

    printf("SNTXERROR in command %s: ( %s ) \n", cmd, cmd2);
}


void FillArrayLabels(struct FileData* asmb, struct Labels* labels[])
{
    assert(asmb != NULL);
    assert(labels != NULL);
    while(1) 
    {
        int cur_cmd = 0, ip = 0, cur_label = 0;
        int arg = 0;
        char str1[50];
        char str2[50];

        if (sscanf(asmb->dinamic_text[cur_cmd], "%s %d", str1, &arg) == 2) 
        {
            ip += 2;                                //считали команду(строку) и число
        }

        else 
        {
            if (strchr(str1, ':') != NULL)
            {
                strcpy(labels[cur_label]->name, str1);
                labels[cur_label]->index = ip + 1;
                cur_label++;
            }

            int num_param = sscanf(asmb->dinamic_text[cur_cmd], "%s %s", str1, str2);

            if (num_param == 2)                     //считали 2 строки
                ip += 2;

            else                                    //считали 1 строку
                ip += 1;
        }

        strcpy(labels[cur_label]->name, "0");           //делаем последний элемент массива структур нулём
        labels[cur_label]->index = 0;

        if (strcmp(str1, "hlt") == 0) {
            break;
        }
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