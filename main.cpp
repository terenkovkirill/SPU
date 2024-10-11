#include <TXLib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, const char* argv[])  //файлы для считывания и записи в dump
{
    SPU(argv[1], argv[2]);
}

void SPU(const char* readfile, const char* logfile)
{
    Stack_t stk = {};

    StackCtor(&stk, 2, argv[2]);

    FILE* read_file = fopen(argv[1], "wb");
    FILE* log_file = fopen(argv[2], "wb");

    while(1)
    {
        char cmd[50] = "";
        fscanf(read_file, "%s", cmd);


        if (strcmp(cmd, "push") == 0) {
            int arg = 0;
            fscanf("%d", &arg);
            StackPush(&stk, arg);
        }
        
        else if (strcmp(cmd, "sub") == 0) {
            int value1, value2;
            StackPop(&stk, &value1, log_file);
            StackPop(&stk, &value2, log_file);
            StackPush(&stk, value1 - value2, log_file);
        }

        else if (strcmp(cmd, "add") == 0) {
            int value1, value2;
            StackPop(&stk, &value1, log_file);
            StackPop(&stk, &value2, log_file);
            StackPush(&stk, value1 + value2, log_file);
        }

        else if (strcmp(cmd, "mul") == 0) {
            int value1, value2;
            StackPop(&stk, &value1, log_file);
            StackPop(&stk, &value2, log_file);
            StackPush(&stk, value1 * value2, log_file);
        }

        else if (strcmp(cmd, "hlt") == 0) {
            break;
        }

        else {
            printf("SNTXERR", "%s \n", cmd);
        }
    }

}